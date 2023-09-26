#ifndef S21_STACK_H
#define S21_STACK_H

#include "../list/s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class stack {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  stack() : container_() {}

  stack(std::initializer_list<value_type> const &items) : container_(items) {}

  stack(const stack &s) : container_(s.container_) {}

  stack(stack &&s) noexcept : container_(std::move(s.container_)) {}

  ~stack() = default;

  stack &operator=(stack &&s) noexcept {
    if (this != &s) {
      container_.clear();
      stack nw(std::move(s));
      swap(nw);
    }
    return *this;
  }

  stack &operator=(const stack &s) {
    if (this != &s) {
      container_.clear();
      stack nw(s);
      swap(nw);
    }
    return *this;
  }

  const_reference top() const noexcept { return container_.back(); }

  bool empty() const noexcept { return container_.empty(); }

  size_type size() const noexcept { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_back(); }

  void swap(stack &other) { container_.swap(other.container_); }

 private:
  Container container_;
};

};  // namespace s21

#endif  // S21_STACK_H