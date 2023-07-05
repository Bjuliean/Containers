#ifndef NODE_HPP
#define NODE_HPP

namespace s21 {

template <class T>
class Node {
public:
    T* data_;
    Node<T>* pNext_;
    Node<T>* pPrev_;

    Node() : pNext_(nullptr), pPrev_(nullptr) {}

    Node(const T& data) : data_(data), pNext_(nullptr), pPrev_(nullptr) {}

    Node(const T& data, Node<T>* pNext, Node<T>* pPrev) : data_(data), pNext_(pNext), pPrev_(pPrev) {}
};

}; // namespace s21

#endif // NODE_HPP