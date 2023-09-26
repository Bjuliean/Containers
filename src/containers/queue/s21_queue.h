#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../list/s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  queue() : container_() {}

  queue(std::initializer_list<value_type> const &items) : container_(items) {}

  queue(const queue &q) : container_(q.container_) {}

  queue(queue &&q) noexcept : container_(std::move(q.container_)) {}

  ~queue() = default;

  queue &operator=(queue &&q) noexcept {
    if (this != &q) {
      container_.clear();
      queue nw(std::move(q));
      swap(nw);
    }
    return *this;
  }

  queue &operator=(const queue &q) {
    if (this != &q) {
      container_.clear();
      queue nw(q);
      swap(nw);
    }
    return *this;
  }

  const_reference front() const noexcept { return container_.front(); }

  const_reference back() const noexcept { return container_.back(); }

  bool empty() const noexcept { return container_.empty(); }

  size_type size() const noexcept { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_front(); }

  void swap(queue &other) { container_.swap(other.container_); }

 private:
  Container container_;
};

};  // namespace s21

#endif  // S21_QUEUE_H