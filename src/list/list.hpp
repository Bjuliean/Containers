#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include "node.hpp"
#include "iterator.hpp"

namespace s21 {

template <class T, typename Alloc = std::allocator<T>>
class list {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    //using iterator
    //using const_iterator
    using ValueAlloc = Alloc;
    using NodeAlloc = typename std::allocator_traits<Alloc>::rebind_alloc<Node<T>>;

    list() : size_(0) { CreateFakeNode(); }

    list(size_type n) {
        CreateFakeNode();
        while(n-- > 0)
            push_back(0);
    }

    list(std::initializer_list<value_type> const &items) {
        CreateFakeNode();
        for(auto it = items.begin(); it != items.end(); ++it)
            push_back(*it);
    }

    // list(const list &l) {
    //     int size = l.size_;
    //     while(l > 0) {

    //     }
    // }

    ~list() noexcept {
        DeallocateList();
    }

    void pop_back() {
        Node<T>* temp = fake_node_->pPrev_;
        fake_node_->pPrev_->pPrev_->pNext_ = fake_node_;
        fake_node_->pPrev_ = fake_node_->pPrev_->pPrev_;
        (temp->data_)->~T();
        value_alloc.deallocate(temp->data_, 1);
        node_alloc.deallocate(temp, 1);
    }

    void pop_front() {
        Node<T>* temp = fake_node_->pNext_;
        fake_node_->pNext_->pNext_->pPrev_ = fake_node_;
        fake_node_->pNext_ = fake_node_->pNext_->pNext_;
        (temp->data_)->~T();
        value_alloc.deallocate(temp->data_, 1);
        node_alloc.deallocate(temp, 1);
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

    void out() {
        Node<T>* temp = fake_node_->pNext_;
        Node<T>* t;
        while(temp != fake_node_) {
            t = temp;
            std::cout << *(temp->data_) << std::endl;
            temp = temp->pNext_;
        }
    }

private:
    Node<T>* fake_node_;
    int size_;
    ValueAlloc value_alloc;
    NodeAlloc node_alloc;

    void CreateFakeNode() {
        fake_node_ = node_alloc.allocate(1);
        fake_node_->data_ = value_alloc.allocate(1);
        fake_node_->pNext_ = fake_node_;
        fake_node_->pPrev_ = fake_node_;
    }

    Node<T>* CreateNode(const_reference value, Node<T>* pNext, Node<T>* pPrev) {
        Node<T>* nw = node_alloc.allocate(1);
        nw->data_ = value_alloc.allocate(1);
        try {
            node_alloc.construct(nw);
            value_alloc.construct(nw->data_, value);
            nw->pNext_ = pNext;
            nw->pPrev_ = pPrev;
        } catch(...) {
            value_alloc.deallocate(nw->data_, 1);
            node_alloc.deallocate(nw, 1);
        }
        return nw;
    }

    void DeallocateList() {
        Node<T>* temp = fake_node_->pNext_;
        Node<T>* t;
        while(temp != fake_node_) {
            t = temp;
            temp = temp->pNext_;
            (t->data_)->~T();
            value_alloc.deallocate(t->data_, 1);
            node_alloc.deallocate(t, 1);
        }
        value_alloc.deallocate(fake_node_->data_, 1);
        node_alloc.deallocate(fake_node_, 1);
        size_ = 0;
    }

};

}; // namespace s21

#endif // LIST_HPP