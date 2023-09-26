#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>

#include "s21_rbtree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using pointer = value_type*;
  using const_reference = const value_type&;
  using const_pointer = const pointer*;
  using iterator = typename s21::rbtree<Key, Compare>::RBTreeIteratorSet;
  using const_iterator =
      typename s21::rbtree<Key, Compare>::ConstRBTreeIteratorSet;
  using size_type = size_t;

  set() : tree_() {}

  set(std::initializer_list<value_type> const& items) {
    for (auto it : items) insert(it);
  }

  set(set&& s) noexcept { tree_.Move(std::move(s.tree_)); }

  set(const set& s) { tree_.CopyTree(s.tree_); }

  ~set() = default;

  set& operator=(set&& s) noexcept {
    if (this != &s) {
      clear();
      set nw(std::move(s));
      swap(nw);
    }
    return *this;
  }

  set& operator=(const set& s) {
    if (this != &s) {
      clear();
      tree_.CopyTree(s.tree_);
    }
    return *this;
  }

  iterator begin() noexcept { return tree_.begin_set(); }

  iterator end() noexcept { return tree_.end_set(); }

  const_iterator cbegin() const noexcept { return tree_.cbegin_set(); }

  const_iterator cend() const noexcept { return tree_.cend_set(); }

  bool empty() const noexcept { return tree_.Size() == 0; }

  size_type size() const noexcept { return tree_.Size(); }

  size_type max_size() const noexcept {
    return PTRDIFF_MAX / sizeof(value_type);
  }

  void clear() { tree_.Clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree_.InsertByKey(value);
  }

  void erase(iterator pos) { tree_.EraseNodeSet(pos); }

  void swap(set& other) { tree_.Swap(other.tree_); }

  void merge(set& other) { tree_.MergeTrees(other.tree_); }

  iterator find(const Key& key) { return tree_.Find(key); }

  bool contains(const Key& key) const noexcept { return tree_.Contains(key); }

 private:
  s21::rbtree<Key, Compare> tree_;

};  // set

};  // namespace s21

#endif  // S21_SET_H