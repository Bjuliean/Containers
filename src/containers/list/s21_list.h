#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T>
struct Node {
 public:
  T* data_;
  Node<T>* pNext_;
  Node<T>* pPrev_;

  Node(Node<T>* pNext = nullptr, Node<T>* pPrev = nullptr)
      : pNext_(pNext), pPrev_(pPrev) {}

  Node(const T& data, Node<T>* pNext = nullptr, Node<T>* pPrev = nullptr)
      : data_(data), pNext_(pNext), pPrev_(pPrev) {}
};

template <typename T, typename Alloc = std::allocator<T>>
class list {
 public:
  class ListIterator;
  class ConstListIterator;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_pointer = const T*;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ConstListIterator;
  using size_type = size_t;
  using alloc_value = Alloc;
  using alloc_node =
      typename std::allocator_traits<Alloc>::rebind_alloc<Node<T>>;

  list() : size_(0) { InitFakeNode(); }

  list(size_type n) : size_(0) {
    InitFakeNode();
    for (size_type i = 0; i < n; i++) push_back(value_type());
  }

  list(std::initializer_list<value_type> const& items) : size_(0) {
    InitFakeNode();
    for (auto it = items.begin(); it != items.end(); ++it) push_back(*it);
  }

  list(const list& l) : size_(0) {
    InitFakeNode();
    for (auto it = l.begin(); it != l.end(); it++) push_back(*it);
  }

  list(list&& l) noexcept : fake_node_(l.fake_node_), size_(l.size_) {
    l.fake_node_ = nullptr;
    l.size_ = 0;
  }

  ~list() noexcept { DeallocateList(); }

  list& operator=(list&& l) noexcept {
    if (this != &l) {
      clear();
      list nw(std::move(l));
      swap(nw);
    }
    return *this;
  }

  list& operator=(const list& l) {
    if (this != &l) {
      clear();
      for (auto it = l.begin(); it != l.end(); it++) push_back(*it);
    }
    return *this;
  }

  const_reference front() const {
    if (size_ == 0)
      throw std::out_of_range("Getting front() from empty container\n");
    return *(fake_node_->pNext_->data_);
  }

  const_reference back() const {
    if (size_ == 0)
      throw std::out_of_range("Getting back() from empty container\n");
    return *(fake_node_->pPrev_->data_);
  }

  void push_front(const_reference value) {
    fake_node_->pNext_ = CreateNode(value, fake_node_->pNext_, fake_node_);
    fake_node_->pNext_->pNext_->pPrev_ = fake_node_->pNext_;
    size_++;
  }

  void push_back(const_reference value) {
    fake_node_->pPrev_ = CreateNode(value, fake_node_, fake_node_->pPrev_);
    fake_node_->pPrev_->pPrev_->pNext_ = fake_node_->pPrev_;
    size_++;
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(fake_node_->pNext_);
  }

  const_iterator cend() const noexcept { return const_iterator(fake_node_); }

  iterator begin() const noexcept { return iterator(fake_node_->pNext_); }

  iterator end() const noexcept { return iterator(fake_node_); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return alloc_n.max_size(); }

  void clear() {
    DeallocateList();
    InitFakeNode();
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    pos.ptr_->pPrev_ = CreateNode(value, pos.ptr_, pos.ptr_->pPrev_);
    pos.ptr_->pPrev_->pPrev_->pNext_ = pos.ptr_->pPrev_;
    size_++;
    return iterator(pos.ptr_->pPrev_);
  }

  void erase(iterator pos) {
    if (pos != iterator(fake_node_)) {
      pos.ptr_->pPrev_->pNext_ = pos.ptr_->pNext_;
      pos.ptr_->pNext_->pPrev_ = pos.ptr_->pPrev_;
      DeallocateNode(pos.ptr_);
      size_--;
    }
  }

  void pop_back() { erase(iterator(fake_node_->pPrev_)); }

  void pop_front() { erase(iterator(fake_node_->pNext_)); }

  void unique() {
    auto it = this->begin();
    while (it != this->end()) {
      auto cur = it;
      auto next = ++it;
      if (it == this->end()) break;
      if (*cur == *next) erase(cur);
    }
  }

  void swap(list& other) {
    std::swap(fake_node_, other.fake_node_);
    std::swap(size_, other.size_);
  }

  void reverse() {
    for (auto it = this->begin(); it != this->end(); it--) {
      std::swap(it.ptr_->pNext_, it.ptr_->pPrev_);
    }
    std::swap(fake_node_->pNext_, fake_node_->pPrev_);
  }

  void sort() {
    iterator temp;
    for (auto iti = this->begin(); iti != this->end(); iti++) {
      temp = this->begin();
      for (auto itz = this->begin(); itz != this->end(); itz++) {
        if (*temp > *itz) {
          std::swap(*temp, *itz);
        }
        if (itz != this->begin()) temp++;
      }
    }
  }

  void splice(const_iterator pos, list& other) {
    if (other.size_ > 0) {
      auto itb = other.begin();
      auto ite = other.end().operator--();
      pos.ptr_->pPrev_->pNext_ = itb.ptr_;
      itb.ptr_->pPrev_ = pos.ptr_->pPrev_;
      pos.ptr_->pPrev_ = ite.ptr_;
      ite.ptr_->pNext_ = pos.ptr_;
      size_ += other.size_;
      other.DeallocateNode(other.fake_node_);
      other.fake_node_ = nullptr;
      other.size_ = 0;
    }
  }

  void merge(list& other) {
    if (this != &other) {
      auto it = this->begin();
      auto ito = other.begin();
      while (ito != other.end()) {
        if (it == this->end() || *it > *ito) {
          insert(it, *ito);
          ito++;
        } else {
          it++;
        }
      }
      other.DeallocateList();
      other.fake_node_ = nullptr;
    }
  }

  class ConstListIterator {
   public:
    friend list<T>;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    ConstListIterator() noexcept : ptr_(nullptr) {}

    ConstListIterator(Node<T>* ptr) : ptr_(ptr) {}

    const_reference operator*() const { return *(ptr_->data_); }

    const_pointer operator->() const { return ptr_->data_; }

    ConstListIterator& operator++() {
      ptr_ = ptr_->pNext_;
      return *this;
    }

    ConstListIterator operator++(int) {
      ConstListIterator temp = *this;
      ++(*this);
      return temp;
    }

    ConstListIterator& operator--() {
      ptr_ = ptr_->pPrev_;
      return *this;
    }

    ConstListIterator operator--(int) {
      ConstListIterator temp = *this;
      --(*this);
      return temp;
    }

    friend bool operator==(const ConstListIterator& lhs,
                           const ConstListIterator& rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const ConstListIterator& lhs,
                           const ConstListIterator& rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

   protected:
    Node<T>* ptr_;

  };  // ConstListIterator

  class ListIterator : public ConstListIterator {
   public:
    ListIterator() { this->ptr_ = nullptr; }

    ListIterator(Node<T>* ptr) { this->ptr_ = ptr; }

    reference operator*() { return *(this->ptr_->data_); }

    pointer operator->() { return this->ptr_->data_; }

    ListIterator& operator++() {
      ConstListIterator::operator++();
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      ConstListIterator::operator++();
      return temp;
    }

    ListIterator& operator--() {
      ConstListIterator::operator--();
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator temp = *this;
      ConstListIterator::operator--();
      return temp;
    }

    friend bool operator==(const ListIterator& lhs, const ListIterator& rhs) {
      return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const ListIterator& lhs, const ListIterator& rhs) {
      return lhs.ptr_ != rhs.ptr_;
    }

  };  // ListIterator

 private:
  Node<T>* fake_node_;
  size_type size_;
  alloc_value alloc_v;
  alloc_node alloc_n;

  void InitFakeNode() {
    fake_node_ = std::allocator_traits<alloc_node>::allocate(alloc_n, 1);
    fake_node_->data_ =
        std::allocator_traits<alloc_value>::allocate(alloc_v, 1);
    try {
      std::allocator_traits<alloc_value>::construct(alloc_v, fake_node_->data_,
                                                    T());
    } catch (...) {
      std::allocator_traits<alloc_value>::deallocate(alloc_v, fake_node_->data_,
                                                     1);
      std::allocator_traits<alloc_node>::deallocate(alloc_n, fake_node_, 1);
      throw;
    }
    fake_node_->pNext_ = fake_node_;
    fake_node_->pPrev_ = fake_node_;
  }

  Node<T>* CreateNode(const_reference value, Node<T>* pNext, Node<T>* pPrev) {
    Node<T>* nw = std::allocator_traits<alloc_node>::allocate(alloc_n, 1);
    nw->data_ = std::allocator_traits<alloc_value>::allocate(alloc_v, 1);
    try {
      std::allocator_traits<alloc_node>::construct(
          alloc_n, nw, std::move_if_noexcept(pNext),
          std::move_if_noexcept(pPrev));
      std::allocator_traits<alloc_value>::construct(
          alloc_v, nw->data_, std::move_if_noexcept(value));
    } catch (...) {
      DeallocateNode(nw);
      DeallocateList();
      throw;
    }

    return nw;
  }

  void DeallocateNode(Node<T>* node) {
    std::allocator_traits<alloc_value>::destroy(alloc_v, node->data_);
    std::allocator_traits<alloc_value>::deallocate(alloc_v, node->data_, 1);
    std::allocator_traits<alloc_node>::deallocate(alloc_n, node, 1);
  }

  void DeallocateList() {
    if (fake_node_ != nullptr) {
      Node<T>* temp = fake_node_->pNext_;
      Node<T>* t;
      while (temp != fake_node_) {
        t = temp;
        temp = temp->pNext_;
        DeallocateNode(t);
      }
      DeallocateNode(fake_node_);
    }
  }

};  // list

};  // namespace s21

#endif  // S21_LIST_H