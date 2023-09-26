#ifndef S21_VECTOR_ITERATOR_H
#define S21_VECTOR_ITERATOR_H

#include <cstddef>
#include <iterator>

#include "s21_vector.h"

namespace s21 {

template <typename T, bool IsIterConst = false>
struct VectorIterator {
 public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_pointer = const T*;
  using const_reference = const T&;
  using difference_type = ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;
  using meta_pointer = std::conditional_t<IsIterConst, const_pointer, pointer>;
  using meta_reference =
      std::conditional_t<IsIterConst, const_reference, reference>;

  VectorIterator() noexcept : ptr_(nullptr) {}

  VectorIterator(pointer ptr) : ptr_(ptr) {}

  meta_reference operator*() const { return *ptr_; }

  meta_pointer operator->() const { return ptr_; }

  VectorIterator& operator++() {
    ++ptr_;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator temp = *this;
    ++(*this);
    return temp;
  }

  VectorIterator& operator--() {
    --ptr_;
    return *this;
  }

  VectorIterator operator--(int) {
    VectorIterator temp = *this;
    --(*this);
    return temp;
  }

  VectorIterator operator+(difference_type rhs) const {
    return VectorIterator(ptr_ + rhs);
  }

  friend VectorIterator operator+(difference_type lhs,
                                  const VectorIterator& rhs) {
    return VectorIterator(lhs + rhs.ptr_);
  }

  friend difference_type operator+(const VectorIterator& lhs,
                                   const VectorIterator& rhs) {
    return (lhs.ptr_ + rhs.ptr_);
  }

  VectorIterator operator-(difference_type rhs) const {
    return VectorIterator(ptr_ - rhs);
  }

  friend VectorIterator operator-(difference_type lhs,
                                  const VectorIterator& rhs) {
    return VectorIterator(lhs - rhs.ptr_);
  }

  friend difference_type operator-(const VectorIterator& lhs,
                                   const VectorIterator& rhs) {
    return (lhs.ptr_ - rhs.ptr_);
  }

  VectorIterator& operator+=(difference_type lhs) {
    ptr_ += lhs;
    return *this;
  }

  VectorIterator& operator-=(difference_type lhs) {
    ptr_ -= lhs;
    return *this;
  }

  friend bool operator==(const VectorIterator& lhs,
                         const VectorIterator& rhs) noexcept {
    return lhs.ptr_ == rhs.ptr_;
  }

  friend bool operator!=(const VectorIterator& lhs,
                         const VectorIterator& rhs) noexcept {
    return lhs.ptr_ != rhs.ptr_;
  }

  friend bool operator>(const VectorIterator& lhs,
                        const VectorIterator& rhs) noexcept {
    return lhs.ptr_ > rhs.ptr_;
  }

  friend bool operator<(const VectorIterator& lhs,
                        const VectorIterator& rhs) noexcept {
    return lhs.ptr_ < rhs.ptr_;
  }

  friend bool operator>=(const VectorIterator& lhs,
                         const VectorIterator& rhs) noexcept {
    return lhs.ptr_ >= rhs.ptr_;
  }

  friend bool operator<=(const VectorIterator& lhs,
                         const VectorIterator& rhs) noexcept {
    return lhs.ptr_ <= rhs.ptr_;
  }

 private:
  pointer ptr_;
};

};  // namespace s21

#endif  // S21_VECTOR_ITERATOR_H