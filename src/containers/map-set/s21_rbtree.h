#ifndef S21_RBTREE_H
#define S21_RBTREE_H

#include <iterator>
#include <memory>
#include <stdexcept>

namespace s21 {

enum Colors { black, red };

template <typename Key, typename T>
struct RBNode {
  RBNode<Key, T>* pParent_;
  RBNode<Key, T>* pLeft_;
  RBNode<Key, T>* pRight_;
  std::pair<Key, T>* data_;
  Colors color_;

  RBNode(std::pair<Key, T> data = nullptr, RBNode<Key, T>* pLeft = nullptr,
         RBNode<Key, T>* pRight = nullptr, RBNode<Key, T>* pParent = nullptr,
         Colors color = red)
      : data_(data),
        pLeft_(pLeft),
        pRight_(pRight),
        pParent_(pParent),
        color_(color) {}
};

template <typename Key, typename T = int8_t, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<std::pair<Key, T>>>
class rbtree {
 public:
  class RBTreeIterator;
  class ConstRBTreeIterator;
  class ConstRBTreeIteratorSet;
  class RBTreeIteratorSet;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = std::pair<key_type, mapped_type>&;
  using pointer = std::pair<key_type, mapped_type>*;
  using const_reference = const std::pair<key_type, mapped_type>&;
  using const_pointer = const std::pair<key_type, mapped_type>*;
  using size_type = size_t;
  using alloc_value = Alloc;
  using alloc_node = typename std::allocator_traits<Alloc>::rebind_alloc<
      RBNode<key_type, mapped_type>>;
  using iterator = RBTreeIterator;
  using const_iterator = ConstRBTreeIterator;

  rbtree() : size_(0) { InitFakeNode(); }

  ~rbtree() {
    if (fake_node_ != nullptr && fake_node_->pRight_ != nullptr) {
      DeallocateTree(fake_node_->pRight_);
    }
    DeallocateNode(fake_node_);
  }

  RBTreeIteratorSet begin_set() { return RBTreeIteratorSet(min_node_, this); }

  RBTreeIteratorSet end_set() { return RBTreeIteratorSet(this); }

  ConstRBTreeIteratorSet cbegin_set() {
    return ConstRBTreeIteratorSet(min_node_, this);
  }

  ConstRBTreeIteratorSet cend_set() { return ConstRBTreeIteratorSet(this); }

  iterator begin() { return iterator(min_node_, this); }

  iterator end() { return iterator(this); }

  const_iterator cbegin() { return const_iterator(min_node_, this); }

  const_iterator cend() { return const_iterator(this); }

  std::pair<RBTreeIteratorSet, bool> InsertByKey(key_type k) {
    RBNode<key_type, mapped_type>* ptr = Search(fake_node_->pRight_, k);
    bool inserted = false;
    if (ptr == nullptr) {
      inserted = true;
      if (size_ == 0) {
        ptr = fake_node_->pRight_ = CreateNode(std::make_pair(k, mapped_type()),
                                               fake_node_, nullptr, nullptr);
        fake_node_->pRight_->color_ = black;
      } else {
        ptr = PushNode(GetRoot(), k, mapped_type());
      }
      BalanceTree(ptr);
      UpdateMinMax();
      size_++;
    }
    return std::pair<RBTreeIteratorSet, bool>(RBTreeIteratorSet(ptr, this),
                                              inserted);
  }

  std::pair<iterator, bool> InsertByKeyAndValue(key_type k, mapped_type val) {
    RBNode<key_type, mapped_type>* ptr = Search(fake_node_->pRight_, k);
    bool inserted = false;
    if (ptr == nullptr) {
      inserted = true;
      if (size_ == 0) {
        ptr = fake_node_->pRight_ =
            CreateNode(std::make_pair(k, val), fake_node_, nullptr, nullptr);
        fake_node_->pRight_->color_ = black;
      } else {
        ptr = PushNode(GetRoot(), k, val);
      }
      BalanceTree(ptr);
      UpdateMinMax();
      size_++;
    }
    return std::pair<iterator, bool>(iterator(ptr, this), inserted);
  }

  std::pair<iterator, bool> InsertOrAssign(Key k, T obj) {
    RBNode<key_type, mapped_type>* ptr = Search(fake_node_->pRight_, k);
    bool inserted = false;
    if (ptr == nullptr) {
      inserted = true;
      return InsertByKeyAndValue(k, obj);
    }
    ptr->data_->second = obj;
    return std::pair<iterator, bool>(iterator(ptr, this), inserted);
  }

  void Clear() {
    if (fake_node_->pRight_ != nullptr) DeallocateTree(fake_node_->pRight_);
    fake_node_->pRight_ = nullptr;
    size_ = 0;
  }

  RBNode<key_type, mapped_type>* GetMinNodeFromCurrent(
      RBNode<key_type, mapped_type>* node) const {
    RBNode<key_type, mapped_type>* temp = node;
    while (temp->pLeft_ != nullptr) temp = temp->pLeft_;
    return temp;
  }

  RBNode<key_type, mapped_type>* GetMaxNodeFromCurrent(
      RBNode<key_type, mapped_type>* node) const {
    RBNode<key_type, mapped_type>* temp = node;
    while (temp->pRight_ != nullptr) temp = temp->pRight_;
    return temp;
  }

  RBNode<key_type, mapped_type>* GetMinNode() const {
    return GetMinNodeFromCurrent(GetRoot());
  }

  RBNode<key_type, mapped_type>* GetMaxNode() const {
    return GetMaxNodeFromCurrent(GetRoot());
  }

  void EraseNodeSet(RBTreeIteratorSet it) {
    EraseNode(iterator(it.ptr_, this));
  }

  void EraseNode(iterator it) {
    if (it == iterator(fake_node_->pRight_, this) && size_ == 1) {
      DeallocateNode(fake_node_->pRight_);
      fake_node_->pRight_ = nullptr;
    } else {
      EraseProccess(it.ptr_);
      DeallocateNode(it.ptr_);
      UpdateMinMax();
    }
    size_--;
  }

  void MergeTrees(rbtree& other) {
    if (other.GetRoot() != nullptr && this != &other) {
      for (auto it = other.begin(); it != other.end(); it++) {
        InsertByKeyAndValue(it.ptr_->data_->first, it.ptr_->data_->second);
      }
      other.DeallocateTree(other.fake_node_->pRight_);
      other.fake_node_->pRight_ = nullptr;
      other.size_ = 0;
    }
  }

  bool Contains(key_type k) const { return Search(GetRoot(), k) != nullptr; }

  RBTreeIteratorSet Find(const key_type& k) {
    return RBTreeIteratorSet(Search(GetRoot(), k), this);
  }

  T& SearchForKeyAt(const Key& key) {
    RBNode<key_type, mapped_type>* node = Search(fake_node_->pRight_, key);
    if (node == nullptr) throw std::out_of_range("'At' out of range.");
    return node->data_->second;
  }

  size_type Size() const noexcept { return size_; }

  void UpdateMinMax() {
    min_node_ = GetMinNode();
    max_node_ = GetMaxNode();
  }

  void Swap(rbtree& other) {
    std::swap(fake_node_, other.fake_node_);
    std::swap(min_node_, other.min_node_);
    std::swap(max_node_, other.max_node_);
    std::swap(size_, other.size_);
    std::swap(alloc_v, other.alloc_v);
    std::swap(alloc_n, other.alloc_n);
    std::swap(comp, other.comp);
  }

  void Move(rbtree&& other) noexcept {
    if (this != &other) {
      fake_node_->pRight_ = std::move(other.fake_node_->pRight_);
      other.fake_node_->pRight_ = nullptr;
      min_node_ = std::move(other.min_node_);
      other.min_node_ = nullptr;
      max_node_ = std::move(other.max_node_);
      other.max_node_ = nullptr;
      size_ = std::move(other.size_);
      other.size_ = 0;
      alloc_v = std::move(other.alloc_v);
      alloc_n = std::move(other.alloc_n);
      comp = std::move(other.comp);
    }
  }

  void CopyTree(const rbtree& other) {
    RBNode<key_type, mapped_type>* temp = other.GetMinNode();
    while (temp != nullptr) {
      InsertByKeyAndValue(temp->data_->first, temp->data_->second);
      temp = GetNextNode(temp, other.max_node_, other.min_node_);
    }
  }

  class ConstRBTreeIterator {
   public:
    friend rbtree<key_type, mapped_type>;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    ConstRBTreeIterator() : ptr_(nullptr), tree_ptr_(nullptr) {}

    ConstRBTreeIterator(rbtree<key_type, mapped_type>* tree_ptr)
        : ptr_(nullptr), tree_ptr_(tree_ptr) {}

    ConstRBTreeIterator(const RBNode<key_type, mapped_type>& ptr,
                        const rbtree<key_type, mapped_type>& tree_ptr)
        : ptr_(ptr), tree_ptr_(tree_ptr) {}

    const_reference operator*() const noexcept { return ptr_->data_; }

    const_pointer operator->() const noexcept { return &ptr_->data_; }

    ConstRBTreeIterator& operator++() {
      ptr_ = tree_ptr_->GetNextNode(ptr_, tree_ptr_->max_node_,
                                    tree_ptr_->min_node_);
      return *this;
    }

    ConstRBTreeIterator operator++(int) {
      ConstRBTreeIterator temp = *this;
      ++(*this);
      return temp;
    }

    ConstRBTreeIterator& operator--() {
      ptr_ = tree_ptr_->GetPrevNode(ptr_, tree_ptr_->max_node_,
                                    tree_ptr_->min_node_);
      return *this;
    }

    ConstRBTreeIterator operator--(int) {
      ConstRBTreeIterator temp = *this;
      --(*this);
      return temp;
    }

    friend bool operator==(const ConstRBTreeIterator& lhs,
                           const ConstRBTreeIterator rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const ConstRBTreeIterator& lhs,
                           const ConstRBTreeIterator rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

   protected:
    RBNode<key_type, mapped_type>* ptr_;
    rbtree* tree_ptr_;

  };  // ConstRBTreeIterator

  class RBTreeIterator : public ConstRBTreeIterator {
   public:
    RBTreeIterator() {
      this->ptr_ = nullptr;
      this->tree_ptr_ = nullptr;
    }

    RBTreeIterator(rbtree<key_type, mapped_type>* tree_ptr) {
      this->ptr_ = nullptr;
      this->tree_ptr_ = tree_ptr;
    }

    RBTreeIterator(RBNode<key_type, mapped_type>* ptr,
                   rbtree<key_type, mapped_type>* tree_ptr) {
      this->ptr_ = ptr;
      this->tree_ptr_ = tree_ptr;
    }

    reference operator*() { return *(this->ptr_->data_); }

    pointer operator->() { return *&(this->ptr_->data_); }

    RBTreeIterator& operator++() {
      ConstRBTreeIterator::operator++();
      return *this;
    }

    RBTreeIterator operator++(int) {
      RBTreeIterator temp = *this;
      ConstRBTreeIterator::operator++();
      return temp;
    }

    RBTreeIterator& operator--() {
      ConstRBTreeIterator::operator--();
      return *this;
    }

    RBTreeIterator operator--(int) {
      RBTreeIterator temp = *this;
      ConstRBTreeIterator::operator--();
      return temp;
    }

    friend bool operator==(const RBTreeIterator& lhs,
                           const RBTreeIterator& rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const RBTreeIterator& lhs,
                           const RBTreeIterator& rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

  };  // RBTreeIterator

  class ConstRBTreeIteratorSet : public ConstRBTreeIterator {
   public:
    ConstRBTreeIteratorSet() {
      this->ptr_ = nullptr;
      this->tree_ptr_ = nullptr;
    }

    ConstRBTreeIteratorSet(rbtree<key_type, mapped_type>* tree_ptr) {
      this->ptr_ = nullptr;
      this->tree_ptr_ = tree_ptr;
    }

    ConstRBTreeIteratorSet(RBNode<key_type, mapped_type>* ptr,
                           rbtree<key_type, mapped_type>* tree_ptr) {
      this->ptr_ = ptr;
      this->tree_ptr_ = tree_ptr;
    }

    key_type& operator*() { return this->ptr_->data_->first; }

    key_type* operator->() { return &(this->ptr_->data_->first); }

    ConstRBTreeIteratorSet& operator++() {
      ConstRBTreeIterator::operator++();
      return *this;
    }

    ConstRBTreeIteratorSet operator++(int) {
      ConstRBTreeIteratorSet temp = *this;
      ConstRBTreeIterator::operator++();
      return temp;
    }

    ConstRBTreeIteratorSet& operator--() {
      ConstRBTreeIterator::operator--();
      return *this;
    }

    ConstRBTreeIteratorSet operator--(int) {
      ConstRBTreeIteratorSet temp = *this;
      ConstRBTreeIterator::operator--();
      return temp;
    }

    friend bool operator==(const ConstRBTreeIteratorSet& lhs,
                           const ConstRBTreeIteratorSet& rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const ConstRBTreeIteratorSet& lhs,
                           const ConstRBTreeIteratorSet& rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

  };  // ConstRBTreeIteratorSet

  class RBTreeIteratorSet : public ConstRBTreeIterator {
   public:
    RBTreeIteratorSet() {
      this->ptr_ = nullptr;
      this->tree_ptr_ = nullptr;
    }

    RBTreeIteratorSet(rbtree<key_type, mapped_type>* tree_ptr) {
      this->ptr_ = nullptr;
      this->tree_ptr_ = tree_ptr;
    }

    RBTreeIteratorSet(RBNode<key_type, mapped_type>* ptr,
                      rbtree<key_type, mapped_type>* tree_ptr) {
      this->ptr_ = ptr;
      this->tree_ptr_ = tree_ptr;
    }

    key_type& operator*() { return this->ptr_->data_->first; }

    key_type* operator->() { return &(this->ptr_->data_->first); }

    RBTreeIteratorSet& operator++() {
      ConstRBTreeIterator::operator++();
      return *this;
    }

    RBTreeIteratorSet operator++(int) {
      RBTreeIteratorSet temp = *this;
      ConstRBTreeIterator::operator++();
      return temp;
    }

    RBTreeIteratorSet& operator--() {
      ConstRBTreeIterator::operator--();
      return *this;
    }

    RBTreeIteratorSet operator--(int) {
      RBTreeIteratorSet temp = *this;
      ConstRBTreeIterator::operator--();
      return temp;
    }

    friend bool operator==(const RBTreeIteratorSet& lhs,
                           const RBTreeIteratorSet& rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const RBTreeIteratorSet& lhs,
                           const RBTreeIteratorSet& rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

  };  // RBTreeIteratorSet

 protected:
  RBNode<key_type, mapped_type>* fake_node_;
  RBNode<key_type, mapped_type>* min_node_;
  RBNode<key_type, mapped_type>* max_node_;
  size_type size_;
  alloc_value alloc_v;
  alloc_node alloc_n;
  Compare comp;

  void InitFakeNode() {
    fake_node_ = std::allocator_traits<alloc_node>::allocate(alloc_n, 1);
    try {
      fake_node_->data_ =
          std::allocator_traits<alloc_value>::allocate(alloc_v, 1);
      std::allocator_traits<alloc_value>::construct(alloc_v, fake_node_->data_,
                                                    value_type());
    } catch (...) {
      std::allocator_traits<alloc_value>::deallocate(alloc_v, fake_node_->data_,
                                                     1);
      throw;
    }
    fake_node_->color_ = black;
    fake_node_->pLeft_ = fake_node_->pParent_ = fake_node_->pRight_ = nullptr;
  }

  RBNode<Key, T>* CreateNode(value_type data,
                             RBNode<key_type, mapped_type>* pParent,
                             RBNode<key_type, mapped_type>* pLeft,
                             RBNode<key_type, mapped_type>* pRight) {
    RBNode<Key, T>* nw =
        std::allocator_traits<alloc_node>::allocate(alloc_n, 1);
    nw->data_ = std::allocator_traits<alloc_value>::allocate(alloc_v, 1);
    try {
      std::allocator_traits<alloc_value>::construct(
          alloc_v, nw->data_, std::move_if_noexcept(data));
    } catch (...) {
      DeallocateNode(nw);
      if (fake_node_ != nullptr && fake_node_->pRight_ != nullptr)
        DeallocateTree(fake_node_->pRight_);
      DeallocateNode(fake_node_);
      throw;
    }
    nw->pParent_ = pParent;
    nw->pLeft_ = pLeft;
    nw->pRight_ = pRight;
    nw->color_ = red;
    return nw;
  }

  void DeallocateTree(RBNode<key_type, mapped_type>* node) {
    if (node->pLeft_ != nullptr) DeallocateTree(node->pLeft_);
    if (node->pRight_ != nullptr) DeallocateTree(node->pRight_);
    DeallocateNode(node);
  }

  void DeallocateNode(RBNode<key_type, mapped_type>* node) {
    std::allocator_traits<alloc_value>::destroy(alloc_v, node->data_);
    std::allocator_traits<alloc_value>::deallocate(alloc_v, node->data_, 1);
    std::allocator_traits<alloc_node>::deallocate(alloc_n, node, 1);
  }

  void BalanceTree(RBNode<key_type, mapped_type>* node) {
    while (node != nullptr && node != GetRoot() &&
           node->pParent_->color_ == red) {
      if (node->pParent_ == node->pParent_->pParent_->pLeft_) {
        if (node->pParent_->pParent_->pRight_ != nullptr &&
            node->pParent_->pParent_->pRight_->color_ == red) {
          node->pParent_->pParent_->pRight_->color_ = node->pParent_->color_ =
              black;
          node->pParent_->pParent_->color_ = red;
          node = node->pParent_->pParent_;
        } else {
          if (node == node->pParent_->pRight_) {
            node = node->pParent_;
            RotateLeft(node);
          }
          node->pParent_->color_ = black;
          node->pParent_->pParent_->color_ = red;
          RotateRight(node->pParent_->pParent_);
        }
      } else if (node->pParent_ == node->pParent_->pParent_->pRight_) {
        if (node->pParent_->pParent_->pLeft_ != nullptr &&
            node->pParent_->pParent_->pLeft_->color_ == red) {
          node->pParent_->pParent_->pLeft_->color_ = node->pParent_->color_ =
              black;
          node->pParent_->pParent_->color_ = red;
          node = node->pParent_->pParent_;
        } else {
          if (node == node->pParent_->pLeft_) {
            node = node->pParent_;
            RotateRight(node);
          }
          node->pParent_->color_ = black;
          node->pParent_->pParent_->color_ = red;
          RotateLeft(node->pParent_->pParent_);
        }
      }
    }
    fake_node_->pRight_->color_ = black;
  }

  RBNode<key_type, mapped_type>* GetNextNode(
      RBNode<key_type, mapped_type>* node, RBNode<key_type, mapped_type>* max,
      RBNode<key_type, mapped_type>* min) {
    if (node == max) {
      node = nullptr;
    } else if (node == nullptr) {
      node = min;
    } else {
      if (node->pRight_ != nullptr) {
        node = node->pRight_;
        while (node->pLeft_ != nullptr) node = node->pLeft_;
      } else if (node->pRight_ == nullptr) {
        while (node != node->pParent_->pLeft_) node = node->pParent_;
        node = node->pParent_;
      }
    }
    return node;
  }

  RBNode<key_type, mapped_type>* GetPrevNode(
      RBNode<key_type, mapped_type>* node, RBNode<key_type, mapped_type>* max,
      RBNode<key_type, mapped_type>* min) {
    if (node == min) {
      node = nullptr;
    } else if (node == nullptr) {
      node = max;
    } else {
      if (node->pLeft_ != nullptr) {
        node = node->pLeft_;
        while (node->pRight_ != nullptr) node = node->pRight_;
      } else if (node->pLeft_ == nullptr) {
        while (node != node->pParent_->pRight_) node = node->pParent_;
        node = node->pParent_;
      }
    }
    return node;
  }

  void ReplaceNode(RBNode<key_type, mapped_type>* current_node,
                   RBNode<key_type, mapped_type>* new_son) {
    if (new_son != nullptr) new_son->pParent_ = current_node->pParent_;
    if (current_node->pParent_ == fake_node_) {
      fake_node_->pRight_ = new_son;
    }
    if (current_node == current_node->pParent_->pLeft_) {
      current_node->pParent_->pLeft_ = new_son;
    } else {
      current_node->pParent_->pRight_ = new_son;
    }
  }

  void EraseProccess(RBNode<key_type, mapped_type>* node) {
    RBNode<key_type, mapped_type>* deleted_node = 0;
    RBNode<key_type, mapped_type>* next_node = node;
    RBNode<key_type, mapped_type>* backup_node = 0;
    Colors node_color = next_node->color_;

    if (node->pLeft_ == nullptr) {
      deleted_node = node->pRight_;
      backup_node = node->pParent_;
      ReplaceNode(node, node->pRight_);
    } else if (node->pRight_ == nullptr) {
      deleted_node = node->pLeft_;
      backup_node = node->pParent_;
      ReplaceNode(node, node->pLeft_);
    } else {
      next_node = GetMinNodeFromCurrent(node->pRight_);
      node_color = next_node->color_;
      deleted_node = next_node->pRight_;
      if (next_node->pParent_ == node) {
        backup_node = node;
      } else {
        ReplaceNode(next_node, next_node->pRight_);
        backup_node = next_node->pParent_;
        next_node->pRight_ = node->pRight_;
        next_node->pRight_->pParent_ = next_node;
      }
      ReplaceNode(node, next_node);
      next_node->pLeft_ = node->pLeft_;
      next_node->pLeft_->pParent_ = next_node;
      next_node->color_ = node->color_;
    }

    if (size_ == 1) {
      fake_node_->pRight_->color_ = black;
    } else {
      if (node_color == black) BalanceAfterDelete(deleted_node, backup_node);
    }
  }

  void BalanceAfterDelete(RBNode<key_type, mapped_type>* node,
                          RBNode<key_type, mapped_type>* backup_node) {
    RBNode<key_type, mapped_type>* sibling_node;
    while (node != GetRoot() && (node == nullptr || node->color_ == black)) {
      if (node == backup_node->pLeft_) {
        sibling_node = backup_node->pRight_;
        if (sibling_node->color_ == red) {
          sibling_node->color_ = black;
          backup_node->color_ = red;
          RotateLeft(backup_node);
          sibling_node = backup_node->pRight_;
        }
        if ((sibling_node->pLeft_ == nullptr ||
             sibling_node->pLeft_->color_ == black) &&
            (sibling_node->pRight_ == nullptr ||
             sibling_node->pRight_->color_ == black)) {
          sibling_node->color_ = red;
          node = backup_node;
          backup_node = backup_node->pParent_;
          if (backup_node == fake_node_) break;
        } else {
          if (sibling_node->pRight_ == nullptr ||
              sibling_node->pRight_->color_ == black) {
            sibling_node->pLeft_->color_ = black;
            sibling_node->color_ = red;
            RotateRight(sibling_node);
            sibling_node = backup_node->pRight_;
          }
          sibling_node->color_ = backup_node->color_;
          backup_node->color_ = black;
          if (sibling_node->pRight_) {
            sibling_node->pRight_->color_ = black;
            RotateLeft(backup_node);
            break;
          }
        }
      } else {
        sibling_node = backup_node->pLeft_;
        if (sibling_node->color_ == red) {
          sibling_node->color_ = black;
          backup_node->color_ = red;
          RotateRight(backup_node);
          sibling_node = backup_node->pLeft_;
          if (sibling_node == nullptr) break;
        }
        if ((sibling_node->pRight_ == nullptr ||
             sibling_node->pRight_->color_ == black) &&
            (sibling_node->pLeft_ == nullptr ||
             sibling_node->pLeft_->color_ == black)) {
          sibling_node->color_ = red;
          node = backup_node;
          backup_node = backup_node->pParent_;
          if (backup_node == fake_node_) break;
        } else {
          if (sibling_node->pLeft_ == nullptr ||
              sibling_node->pLeft_->color_ == black) {
            sibling_node->pRight_->color_ = black;
            sibling_node->color_ = red;
            RotateLeft(sibling_node);
            sibling_node = backup_node->pLeft_;
          }
          sibling_node->color_ = backup_node->color_;
          backup_node->color_ = black;
          if (sibling_node->pLeft_) {
            sibling_node->pLeft_->color_ = black;
            RotateRight(sibling_node->pParent_);
            break;
          }
        }
      }
    }
    if (node != nullptr) node->color_ = black;
  }

  RBNode<key_type, mapped_type>* PushNode(RBNode<key_type, mapped_type>* root,
                                          key_type k, mapped_type val) {
    RBNode<key_type, mapped_type>* ptr = nullptr;
    while (root != nullptr) {
      if (comp(k, root->data_->first)) {
        if (root->pLeft_ == nullptr) {
          ptr = root->pLeft_ =
              CreateNode(std::make_pair(k, val), root, nullptr, nullptr);
          break;
        } else {
          root = root->pLeft_;
        }
      } else {
        if (root->pRight_ == nullptr) {
          ptr = root->pRight_ =
              CreateNode(std::make_pair(k, val), root, nullptr, nullptr);
          break;
        } else {
          root = root->pRight_;
        }
      }
    }
    return ptr;
  }

  RBNode<key_type, mapped_type>* Search(RBNode<key_type, mapped_type>* node,
                                        key_type k) const {
    if (node == nullptr) return nullptr;
    if (node->data_->first == k) return node;
    return comp(k, node->data_->first) ? Search(node->pLeft_, k)
                                       : Search(node->pRight_, k);
  }

  void RotateLeft(RBNode<key_type, mapped_type>* node) {
    RBNode<key_type, mapped_type>* child = node->pRight_;
    node->pRight_ = child->pLeft_;
    if (child->pLeft_ != nullptr) child->pLeft_->pParent_ = node;
    child->pParent_ = node->pParent_;
    if (node == node->pParent_->pRight_)
      node->pParent_->pRight_ = child;
    else
      node->pParent_->pLeft_ = child;
    node->pParent_ = child;
    child->pLeft_ = node;
  }

  void RotateRight(RBNode<key_type, mapped_type>* node) {
    RBNode<key_type, mapped_type>* child = node->pLeft_;
    node->pLeft_ = child->pRight_;
    if (child->pRight_ != nullptr) child->pRight_->pParent_ = node;
    child->pParent_ = node->pParent_;
    if (node == node->pParent_->pRight_)
      node->pParent_->pRight_ = child;
    else
      node->pParent_->pLeft_ = child;
    node->pParent_ = child;
    child->pRight_ = node;
  }

  RBNode<key_type, mapped_type>* GetRoot() const { return fake_node_->pRight_; }

};  // rbtree

};  // namespace s21

#endif  // S21_RBTREE_H
