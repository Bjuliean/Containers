#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace s21 {

template <class T>
class VectorIterator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    VectorIterator() : ptr_(nullptr) {}

    VectorIterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() { return *ptr_; }

    pointer operator->() { return ptr_; }

    VectorIterator& operator++() {
        ptr_++;
        return *this;
    }

    VectorIterator operator ++(int) {
        VectorIterator temp = *this;
        ++(*this);
        return temp;
    }

    VectorIterator operator-(difference_type rhs) { return VectorIterator(ptr_ - rhs); }

    friend difference_type operator-(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ - rhs.ptr_; }

    VectorIterator& operator-=(difference_type rhs) {
        ptr_ -= rhs;
        return *this;
    }

    VectorIterator operator+(difference_type rhs) { return VectorIterator(ptr_ + rhs); }

    friend difference_type operator+(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ + rhs.ptr_; }

    VectorIterator& operator+=(difference_type rhs) {
        ptr_ += rhs;
        return *this;
    }

    friend bool operator==(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ == rhs.ptr_; }

    friend bool operator!=(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ != rhs.ptr_; }

    friend bool operator>(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ > rhs.ptr_; }

    friend bool operator<(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ < rhs.ptr_; }

    friend bool operator>=(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ >= rhs.ptr_; }

    friend bool operator<=(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr_ <= rhs.ptr_; }

private:
    pointer ptr_;

};

}; // namespace s21

#endif // ITERATOR_HPP