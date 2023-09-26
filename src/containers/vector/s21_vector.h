#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>
#include <memory>
#include <stdexcept>

#include "s21_vector_iterator.h"

namespace s21 {

template <typename T, typename Alloc = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_pointer = const T *;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = VectorIterator<T, false>;
  using const_iterator = VectorIterator<T, true>;

  vector() : data_(nullptr), size_(0), capacity_(0) {}

  vector(size_type n) : size_(n), capacity_(n) {
    AllocateMemory();
    for (auto it = this->begin(); it != this->end(); it++)
      std::allocator_traits<Alloc>::construct(alloc, std::addressof(*it), T());
  }

  vector(std::initializer_list<value_type> const &items)
      : size_(items.size()), capacity_(items.size()) {
    AllocateMemory();
    auto data_it = this->begin();
    for (auto it = items.begin(); it != items.end(); it++)
      std::allocator_traits<Alloc>::construct(alloc, std::addressof(*data_it++),
                                              std::move_if_noexcept(*it));
  }

  vector(const vector &v) : size_(v.size_), capacity_(v.capacity_) {
    AllocateMemory();
    std::uninitialized_copy(v.begin(), v.end(), data_);
  }

  vector(vector &&v) noexcept
      : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = v.capacity_ = 0;
  }

  ~vector() { clear(); }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      clear();
      vector nw(std::move(v));
      swap(nw);
    }
    return *this;
  }

  vector &operator=(const vector &v) {
    if (this != &v) {
      clear();
      vector nw(v);
      swap(nw);
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Index out of range.");
    return *iterator(data_ + pos);
  }

  reference operator[](size_type pos) { return *iterator(data_ + pos); }

  const_reference front() const {
    if (size_ == 0)
      throw std::out_of_range("Getting front() from empty vector.");
    return *iterator(data_);
  }

  const_reference back() const {
    if (size_ == 0)
      throw std::out_of_range("Getting back() from empty vector\n");
    return *iterator(data_ + (size_ - 1));
  }

  T *data() { return data_; }

  const_iterator cbegin() const noexcept { return const_iterator(data_); }

  const_iterator cend() const noexcept { return const_iterator(data_ + size_); }

  iterator begin() const noexcept { return iterator(data_); }

  iterator end() const noexcept { return iterator(data_ + size_); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return PTRDIFF_MAX / sizeof(value_type);
  }

  void reserve(size_type size) {
    if (size > capacity_) {
      pointer newdata = std::allocator_traits<Alloc>::allocate(alloc, size);
      size_type i = 0;
      try {
        for (; i < size_; i++)
          std::allocator_traits<Alloc>::construct(
              alloc, newdata + i, std::move_if_noexcept(data_[i]));
      } catch (...) {
        for (size_type j = 0; j < i; j++)
          std::allocator_traits<Alloc>::destroy(alloc, newdata + j);
        std::allocator_traits<Alloc>::deallocate(alloc, newdata, size);
        throw;
      }
      DeallocateMemory();
      data_ = newdata;
      capacity_ = size;
    }
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ > size_) {
      pointer newdata = std::allocator_traits<Alloc>::allocate(alloc, size_);
      size_type i = 0;
      try {
        for (; i < size_; i++)
          std::allocator_traits<Alloc>::construct(
              alloc, newdata + i, std::move_if_noexcept(data_[i]));
      } catch (...) {
        for (size_type j = 0; j < i; j++)
          std::allocator_traits<Alloc>::destroy(alloc, newdata + j);
        std::allocator_traits<Alloc>::deallocate(alloc, newdata, size_);
        throw;
      }
      DeallocateMemory();
      data_ = newdata;
      capacity_ = size_;
    }
  }

  void clear() noexcept {
    DeallocateMemory();
    capacity_ = size_ = 0;
    data_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos < this->begin() || pos > this->end())
      throw std::out_of_range("Iterator out of range");
    size_type new_capacity = capacity_;
    if (size_ + 1 >= capacity_) new_capacity = capacity_ << 1;
    pointer newdata =
        std::allocator_traits<Alloc>::allocate(alloc, new_capacity);
    size_type z = 0;
    iterator it;
    try {
      for (size_type i = 0; i < size_; i++) {
        if (pos == iterator(data_ + i)) {
          it = iterator(newdata + z);
          std::allocator_traits<Alloc>::construct(alloc, newdata + z++,
                                                  std::move_if_noexcept(value));
        }
        std::allocator_traits<Alloc>::construct(
            alloc, newdata + z++, std::move_if_noexcept(data_[i]));
      }
      if (pos == this->end())
        std::allocator_traits<Alloc>::construct(alloc, newdata + z++,
                                                std::move_if_noexcept(value));
    } catch (...) {
      for (size_type i = 0; i < z; i++)
        std::allocator_traits<Alloc>::destroy(alloc, newdata + i);
      std::allocator_traits<Alloc>::deallocate(alloc, newdata, new_capacity);
      throw;
    }
    DeallocateMemory();
    data_ = newdata;
    capacity_ = new_capacity;
    size_++;
    return it;
  }

  void erase(iterator pos) {
    if (pos < this->begin() || pos >= this->end())
      throw std::out_of_range("Iterator out of range");
    pointer newdata = std::allocator_traits<Alloc>::allocate(alloc, capacity_);
    size_type z = 0;
    try {
      for (size_type i = 0; i < size_; i++) {
        if (pos != iterator(data_ + i))
          std::allocator_traits<Alloc>::construct(
              alloc, newdata + z++, std::move_if_noexcept(data_[i]));
      }
    } catch (...) {
      for (size_type i = 0; i < z; i++)
        std::allocator_traits<Alloc>::destroy(alloc, newdata + i);
      std::allocator_traits<Alloc>::deallocate(alloc, newdata, capacity_);
      throw;
    }
    DeallocateMemory();
    data_ = newdata;
    size_--;
  }

  void push_back(const_reference value) {
    if (capacity_ == 0) {
      capacity_ = 1;
      AllocateMemory();
    }
    if (size_ == capacity_) reserve(capacity_ << 1);
    std::allocator_traits<Alloc>::construct(alloc, data_ + size_++,
                                            std::move_if_noexcept(value));
  }

  void pop_back() {
    if (size_ > 0) iterator(data_ + (size_-- - 1))->~T();
  }

  void swap(vector &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(alloc, other.alloc);
  }

 private:
  pointer data_;
  size_type size_;
  size_type capacity_;
  Alloc alloc;

  void AllocateMemory() {
    data_ = std::allocator_traits<Alloc>::allocate(alloc, capacity_);
  }

  void DeallocateMemory() {
    for (size_type i = 0; i < size_; i++)
      std::allocator_traits<Alloc>::destroy(alloc, data_ + i);
    std::allocator_traits<Alloc>::deallocate(alloc, data_, capacity_);
    data_ = nullptr;
  }
};

};  // namespace s21

#endif  // S21_VECTOR_H