#ifndef S21_MAP_H
#define S21_MAP_H

#include <initializer_list>

#include "s21_rbtree.h"

namespace s21 {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<std::pair<Key, T>>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using pointer = value_type*;
  using const_reference = const reference;
  using const_pointer = const pointer;
  using iterator = typename s21::rbtree<Key, T, Compare, Alloc>::iterator;
  using const_iterator =
      typename s21::rbtree<Key, T, Compare, Alloc>::const_iterator;
  using size_type = size_t;

  map() : tree_() {}

  map(std::initializer_list<value_type> const& items) {
    for (auto it : items) insert(it);
  }

  map(const map& m) { tree_.CopyTree(m.tree_); }

  map(map&& m) noexcept { tree_.Move(std::move(m.tree_)); }

  ~map() = default;

  map& operator=(map&& m) noexcept {
    if (this != &m) {
      clear();
      map nw(std::move(m));
      swap(nw);
    }
    return *this;
  }

  map& operator=(const map& m) {
    if (this != &m) {
      clear();
      tree_.CopyTree(m.tree_);
    }
    return *this;
  }

  iterator begin() noexcept { return tree_.begin(); }

  iterator end() noexcept { return tree_.end(); }

  const_iterator cbegin() const noexcept { return tree_.cbegin(); }

  const_iterator cend() const noexcept { return tree_.cend(); }

  mapped_type& at(const Key& key) { return tree_.SearchForKeyAt(key); }

  mapped_type& operator[](const Key& key) {
    auto res = insert(key, {});
    return res.first->second;
  }

  bool contains(const Key& key) const noexcept { return tree_.Contains(key); }

  bool empty() const noexcept { return tree_.Size() == 0; }

  size_type size() const noexcept { return tree_.Size(); }

  size_type max_size() const noexcept {
    return PTRDIFF_MAX / sizeof(value_type);
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    return tree_.InsertByKeyAndValue(value.first, value.second);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return tree_.InsertByKeyAndValue(key, obj);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    return tree_.InsertOrAssign(key, obj);
  }

  void erase(iterator pos) { tree_.EraseNode(pos); }

  void swap(map& other) { tree_.Swap(other.tree_); }

  void merge(map& other) { tree_.MergeTrees(other.tree_); }

  void clear() { tree_.Clear(); }

 private:
  s21::rbtree<Key, T, Compare, Alloc> tree_;

};  // map

};  // namespace s21

#endif  // S21_MAP_H
