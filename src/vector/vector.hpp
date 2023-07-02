#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator.hpp"

namespace s21 {

#define DEFAULT_SIZE 0
#define DEFAULT_CAPACITY 1

template <class T, class Alloc = std::allocator<T>>
class vector {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = size_t;
    using iterator = VectorIterator<T>;

    vector() : size_(DEFAULT_SIZE), capacity_(DEFAULT_CAPACITY) { allocate_memory(); }

    vector(size_type n) : size_(DEFAULT_SIZE), capacity_(n) { allocate_memory(); }

    vector(std::initializer_list<value_type> const &items) : size_(items.size()), capacity_(items.size()) {
        allocate_memory();
        std::uninitialized_copy(items.begin(), items.end(), data_);
    }

    vector(const vector &v) : size_(v.size_), capacity_(v.capacity_) {
        allocate_memory();
        std::uninitialized_copy(v.begin(), v.end(), data_);
    }

    vector(vector &&v) : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
        if(this != v) {
            v.capacity_ = v.size_ = 0;
            v.data_ = nullptr;
        }
    }

    ~vector() noexcept { free_memory(); }

    reference operator=(vector &&v) {
        if(this != v) {
            free_memory();
            size_ = v.size_;
            capacity_ = v.capacity_;
            allocate_memory();
            std::uninitialized_copy(v.begin(), v.end(), data_);
        }
        return *this;
    }

    reference at(size_type pos) { if(pos >= 0 && pos < size_) return *iterator(data_ + pos); }

    reference operator[](size_type pos) { return *iterator(data_ + pos); }

    const_reference front() { return *iterator(data_); }

    const_reference back() { return *iterator(data_ + (size_ - 1)); }

    T* data() { return data_; }

    iterator begin() const { return iterator(data_); }

    iterator end() const { return iterator(data_ + size_); }

    bool empty() { return size_ == 0; }

    size_type size() { return size_; }

    size_type max_size() { return PTRDIFF_MAX / sizeof(value_type); }

    void reserve(size_type size) {
        if(size > capacity_) {
            pointer newdata = alloc.allocate(size);
            std::uninitialized_copy(this->begin(), this->end(), newdata);
            for(int i = 0; i < size_; i++)
                iterator(data_ + i)->~T();
            alloc.deallocate(data_, capacity_);
            data_ = newdata;
            capacity_ = size;
        }
    }

    size_type capacity() { return capacity_; }

    void shrink_to_fit() {
        if(capacity_ > size_) {
            pointer newdata = alloc.allocate(size_);
            std::uninitialized_copy(this->begin(), this->end(), newdata);
            for(int i = 0; i < size_; i++)
                iterator(data_ + i)->~T();
            alloc.deallocate(data_, capacity_);
            data_ = newdata;
            capacity_ = size;
        }
    }

    void clear() {
        for(int i = 0; i < size_; i++)
            iterator(data_ + i)->~T();
        size_ = 0;
    }
    
    void push_back(const_reference value) {
        if(size_ == capacity_) reserve(capacity_ << 1);
        alloc.construct(std::addressof(*iterator(data_ + size_)), value);
        size_++;
    }

    void out() {
        for(int i = 0; i < size_; i++)
            std::cout << *(data_ + i) << std::endl;
    }

    void pop_back() { iterator(data_ + --size_)->~T(); }

    void swap(vector& other) {
        if(this != other) {
            std::swap(data_, other.data_);
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            std::swap(alloc, other.alloc);
        }
    }

    void erase(iterator pos) {
            pointer newdata = alloc.allocate(capacity_);
            int z = 0;
            for(int i = 0; i < size_; i++) {
                if(iterator(data_ + i) != pos)
                    alloc.construct(std::addressof(*iterator(newdata + z++)), *iterator(data_ + i));
            }
            for(int i = 0; i < size_; i++)
                iterator(data_ + i)->~T();
            alloc.deallocate(data_, capacity_);
            data_ = newdata;
            size_--;
    }

    iterator insert(iterator pos, const_reference value) {
        if(size_ + 1 >= capacity_) reserve(2 * capacity_);
        pointer newdata = alloc.allocate(capacity_);
        pointer ptr;
        int z = 0;
        for(int i = 0; i < size_; i++) {
            if(pos == iterator(data_ + i)) {
                ptr = (newdata + z);
                alloc.construct(std::addressof(*iterator(newdata + z++)), value);
            }
            alloc.construct(std::addressof(*iterator(newdata + z++)), *iterator(data_ + i)); 
        }
        for(int i = 0; i < size_; i++)
            iterator(data_ + i)->~T();
        alloc.deallocate(data_, capacity_);
        data_ = newdata;
        size_++;
        return iterator(ptr);
    }

private:
    pointer data_;
    int size_;
    int capacity_;
    Alloc alloc;

    void allocate_memory() { data_ = alloc.allocate(capacity_); }

    void free_memory() {
        for(int i = 0; i < size_; i++)
            iterator(data_ + i)->~T();
        alloc.deallocate(std::addressof(*iterator(data_)), capacity_);
    }

};

}; // namespace s21

#endif // VECTOR_HPP