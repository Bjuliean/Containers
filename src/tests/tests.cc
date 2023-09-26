#include <gtest/gtest.h>

#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "../containers/s21_containers.h"

// VECTOR
TEST(VectorTest, Constructor_default) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.data(), std_v.data());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_n) {
  s21::vector<int> s21_v(5);
  std::vector<int> std_v(5);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_initializer_list_1) {
  s21::vector<int> s21_v{2, 3, 5, 7, 1};
  std::vector<int> std_v{2, 3, 5, 7, 1};
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
}

TEST(VectorTest, Constructor_initializer_list_2) {
  std::initializer_list<int> b;
  s21::vector<int> s21_v{b};
  std::vector<int> std_v{b};
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_copy_1) {
  s21::vector<int> s21_v{2, 3, 5, 7, 1};
  std::vector<int> std_v{2, 3, 5, 7, 1};
  s21::vector<int> s21_copy(s21_v);
  std::vector<int> std_copy(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
  EXPECT_EQ(s21_copy.at(0), std_copy.at(0));
  EXPECT_EQ(s21_copy.at(1), std_copy.at(1));
  EXPECT_EQ(s21_copy.at(2), std_copy.at(2));
  EXPECT_EQ(s21_copy.at(3), std_copy.at(3));
  EXPECT_EQ(s21_copy.at(4), std_copy.at(4));
}

TEST(VectorTest, Constructor_copy_2) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_copy(s21_v);
  std::vector<int> std_v;
  std::vector<int> std_copy(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(VectorTest, Constructor_move_1) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_move(s21_v);
  std::vector<int> std_v;
  std::vector<int> std_move(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_move.capacity(), std_move.capacity());
  EXPECT_EQ(s21_move.empty(), std_move.empty());
}

TEST(VectorTest, Constructor_move_2) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21::vector<int> s21_move(s21_v);
  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_move(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_move.capacity(), std_move.capacity());
  EXPECT_EQ(s21_move.empty(), std_move.empty());
}

TEST(VectorTest, Destructor) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21_v.~vector();

  EXPECT_EQ(0, s21_v.size());
  EXPECT_EQ(0, s21_v.capacity());
  EXPECT_EQ(0, s21_v.data());
}

TEST(VectorTest, Operator_move_1) {
  s21::vector<int> s21_v1{1, 2, 3};
  s21::vector<int> s21_v2;
  s21_v2 = std::move(s21_v1);
  EXPECT_EQ(s21_v2.size(), 3);
  EXPECT_EQ(s21_v2.at(0), 1);
  EXPECT_EQ(s21_v2.at(1), 2);
  EXPECT_EQ(s21_v2.at(2), 3);
}

TEST(VectorTest, Operator_move_2) {
  s21::vector<int> s21_v1{1, 2, 3};
  s21::vector<int> s21_v2{4, 5, 6};
  s21_v2 = std::move(s21_v1);
  EXPECT_EQ(s21_v2.size(), 3);
  EXPECT_EQ(s21_v2.at(0), 1);
  EXPECT_EQ(s21_v2.at(1), 2);
  EXPECT_EQ(s21_v2.at(2), 3);
}

TEST(VectorTest, Element_at) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  std::vector<int> std_v{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
}

TEST(VectorTest, Element_at_throw) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_ANY_THROW(s21_v.at(1));
  EXPECT_ANY_THROW(std_v.at(1));
}

TEST(VectorTest, Element_front) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v.front(), std_v.front());
}

TEST(VectorTest, Element_front_throw) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_ANY_THROW(s21_v.front());
}

TEST(VectorTest, Element_back) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v.back(), std_v.back());
}

TEST(VectorTest, Element_back_throw) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_ANY_THROW(s21_v.back());
}

TEST(VectorTest, Element_operator_square_brackets) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
}

TEST(VectorTest, Element_data) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(*s21_v.data(), *std_v.data());
}

TEST(VectorTest, Capacity_empty_1) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Capacity_empty_2) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Capacity_size_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Capacity_size_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Capacity_capacity_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_capacity_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_3) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_4_throw) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_ANY_THROW(s21_v.reserve(-2));
  EXPECT_ANY_THROW(std_v.reserve(-2));
}

TEST(VectorTest, Capacity_shrink_to_fit_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_shrink_to_fit_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Modifiers_clear_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Modifiers_clear_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Modifiers_insert_1) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.insert(s21_v.begin() + 1, 5);
  std_v.insert(std_v.begin() + 1, 5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, Modifiers_insert_2) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.insert(s21_v.begin() + s21_v.size(), 100);
  std_v.insert(std_v.begin() + std_v.size(), 100);

  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorTest, Modifiers_erase_1) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  std::vector<int> std_v{1, 2, 3, 4};

  s21_v.erase(s21_v.begin() + 1);
  std_v.erase(std_v.begin() + 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, Modifiers_erase_2) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.begin());
  std_v.erase(std_v.begin());

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_erase_3) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.end() - 1);
  std_v.erase(std_v.end() - 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_push_back_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_push_back_2) {
  s21::vector<int> s21_v{1, 2};
  std::vector<int> std_v{1, 2};

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorTest, Modifiers_pop_back_1) {
  s21::vector<int> s21_v{1, 2};

  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();

  EXPECT_EQ(s21_v.size(), 0);
  EXPECT_EQ(s21_v.capacity(), 2);
}

TEST(VectorTest, Modifiers_pop_back_2) {
  s21::vector<int> s21_v;

  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();

  EXPECT_EQ(s21_v.size(), 0);
  EXPECT_EQ(s21_v.capacity(), 0);
}

TEST(VectorTest, Modifiers_swap_1) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v;
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_2) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_3) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy{1, 2};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_4) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy{1, 2, 3, 4, 5, 6};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2, 3, 4, 5, 6};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Helpers_add_memotysize_1) {
  int n = 1000;
  s21::vector<int> s21_v(n);
  std::vector<int> std_v(n);
  s21_v.push_back(1);
  std_v.push_back(1);

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Helpers_add_memotysize_2) {
  int n = 10000;
  s21::vector<int> s21_v(n);
  std::vector<int> std_v(n);
  s21_v.push_back(1);
  std_v.push_back(1);

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Helpers_add_memotysize_3) {
  int n = 100000;
  s21::vector<int> s21_v(n);
  std::vector<int> std_v(n);
  s21_v.push_back(1);
  s21_v.push_back(1);
  s21_v.push_back(1);

  std_v.push_back(1);
  std_v.push_back(1);
  std_v.push_back(1);

  EXPECT_EQ(s21_v.size(), std_v.size());
}

// STACK

TEST(StackTest, Constructor_default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, Constructor_initializer_list_1) {
  s21::stack<int> s21_stack{1, 2, 4};
  EXPECT_EQ(s21_stack.size(), 3);
  EXPECT_EQ(s21_stack.top(), 4);
}

TEST(StackTest, Constructor_initializer_list_2) {
  std::initializer_list<int> b;
  s21::stack<int> s21_stack{b};
  std::stack<int> std_stack{b};
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, Constructor_initializer_list_3) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  EXPECT_EQ(s21_stack.top(), 4);
  EXPECT_EQ(s21_stack.size(), size_t(4));
  EXPECT_EQ(s21_stack.empty(), false);
}

TEST(StackTest, Constructor_copy_1) {
  std::initializer_list<int> il1 = {1, 2, 3};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_copy{s21_stack};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_copy{std_stack};
  EXPECT_EQ(s21_stack_copy.size(), std_stack_copy.size());
  EXPECT_EQ(s21_stack_copy.top(), std_stack_copy.top());
}

TEST(StackTest, Constructor_copy_2) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = s21_stack_1;

  EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_2.size());
    s21_stack_1.pop(), s21_stack_2.pop();
  }
}

TEST(StackTest, Constructor_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_move{s21_stack};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{std_stack};
  EXPECT_EQ(s21_stack_move.size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.top(), std_stack_move.top());
}

TEST(StackTest, Constructor_move_2) {
  s21::stack<char> s21_stack_1 = {'a', 'b', 'c', 'd'};
  s21::stack<char> s21_stack_2 = std::move(s21_stack_1);
  s21::stack<char> s21_stack_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  EXPECT_EQ(s21_stack_1.size(), size_t(0));
  EXPECT_EQ(s21_stack_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
}

TEST(StackTest, Opertator_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_move{il2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Opertator_move_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_move{il2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Opertator_move_3) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_move{il2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_move{il2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Top_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};

  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Empty_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, Empty_2) {
  std::initializer_list<int> il1;

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, Size_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, Size_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, Push_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};
  s21_stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Push_2) {
  std::initializer_list<int> il1;

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};
  s21_stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Push_3) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, Pop_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Pop_2) {
  std::initializer_list<int> il1;

  s21::stack<int> s21_stack{il1};
  std::stack<int> std_stack{il1};
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.size(), 0);
}

TEST(StackTest, Pop_3) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  s21_stack.push(5);
  s21_stack.push(0);
  std_stack.push(5);
  std_stack.push(0);
  s21_stack.pop();
  s21_stack.pop();
  std_stack.pop();
  std_stack.pop();
  s21_stack.push(15);
  s21_stack.push(10);
  std_stack.push(15);
  std_stack.push(10);
  s21_stack.pop();
  std_stack.pop();
  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, Swap_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(StackTest, Swap_2) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(StackTest, Swap_3) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2;

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(StackTest, Swap_4) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(StackTest, Swap_5) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2;

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
}

TEST(StackTest, Swap_6) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{il1};
  s21::stack<int> s21_stack_swap{il2};
  std::stack<int> std_stack{il1};
  std::stack<int> std_stack_swap{il2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(StackTest, Swap_7) {
  s21::stack<std::string> s21_stack_1 = {"asdqwe123", "lgfjslsdfgj3",
                                         "qqqqwwwe", "431gtt4"};
  s21::stack<std::string> s21_stack_2 = {"pppppppppsw", "lolsdoallo",
                                         "iioiooioioioad"};
  s21::stack<std::string> s21_stack_3 = {"asdqwe123", "lgfjslsdfgj3",
                                         "qqqqwwwe", "431gtt4"};
  s21::stack<std::string> s21_stack_4 = {"pppppppppsw", "lolsdoallo",
                                         "iioiooioioioad"};

  s21_stack_1.swap(s21_stack_2);

  EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
  EXPECT_EQ(s21_stack_2.size(), s21_stack_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_stack_3.top(), s21_stack_2.top());
    EXPECT_EQ(s21_stack_3.size(), s21_stack_2.size());
    s21_stack_3.pop(), s21_stack_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_stack_1.top(), s21_stack_4.top());
    EXPECT_EQ(s21_stack_1.size(), s21_stack_4.size());
    s21_stack_1.pop(), s21_stack_4.pop();
  }
}

// // LIST

template <typename value_type>
bool compare_lists(s21::list<value_type> my_list,
                   std::list<value_type> std_list) {
  bool result = true;
  if (my_list.size() == std_list.size()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i < my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(ListTest, CompareLists) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  EXPECT_TRUE(compare_lists(my_list, std_list));
  std_list.push_back(6);
  EXPECT_FALSE(compare_lists(my_list, std_list));
  std_list.pop_back();
  my_list.push_front(0);
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, DefaultConstructor) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), 0);
  EXPECT_TRUE(my_list.empty());

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, SizeConstructor) {
  s21::list<int> my_list(1000000);
  std::list<int> std_list(1000000);
  EXPECT_EQ(my_list.size(), 1000000);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> my_list{1, 2, 3, 7, 9};
  std::list<int> std_list{1, 2, 3, 7, 9};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, InitializerListConstructor_2) {
  std::initializer_list<int> b;
  s21::list<int> my_list{b};
  std::list<int> std_list{b};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, CopyConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListTest, MoveAssignmentOperatorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListTest, Front) {
  s21::list<int> my_list{99, 2, 3, 4, 5};
  std::list<int> std_list{99, 2, 3, 4, 5};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListTest, Back) {
  s21::list<int> my_list{1, 2, 3, 4, 99};
  std::list<int> std_list{1, 2, 3, 4, 99};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListTest, Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.empty(), std_list.empty());
  my_list.push_back(10);
  std_list.push_back(10);
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListTest, Size) {
  s21::list<int> my_list{1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, SizeEmpty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, MaxSize) {
  s21::list<size_t> my_list_empty;
  std::list<size_t> std_list_empty;
  EXPECT_EQ(my_list_empty.max_size(), std_list_empty.max_size());
}

TEST(ListTest, Clear) {
  s21::list<int> my_list{1, 2, 3, 4};
  my_list.clear();
  std::list<int> std_list{1, 2, 5, 4, 3};
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, ClearEmpty) {
  s21::list<int> my_list;
  my_list.clear();
  std::list<int> std_list;
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PushBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_back(6);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_back();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PushFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_front(0);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_front();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Swap) {
  s21::list<int> my_list1{1, 2, 3, 4, 5};
  s21::list<int> my_list2{6, 7, 8, 9, 10, 11};
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 2, 3, 4, 5};
  std::list<int> std_list2{6, 7, 8, 9, 10, 11};
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListTest, Swap_2) {
  s21::list<int> my_list1{1, 5, 8, 100};
  s21::list<int> my_list2;
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 5, 8, 100};
  std::list<int> std_list2;
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListTest, begin_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, begin_2) {
  s21::list<int> my_list1(4);

  std::list<int> std_list2(4);
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, begin_3_throw) {
  s21::list<int> my_list1;
  std::list<int> std_list2;

  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, end_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, Merge_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_3) {
  s21::list<int> my_list1{1, 20000, 666};
  s21::list<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_5) {
  s21::list<int> my_list1{1, 20000, 666};
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_6) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Reverse_1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Reverse_2) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Reverse_3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_1) {
  s21::list<int> my_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  std::list<int> std_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_2) {
  s21::list<int> my_list(3);
  std::list<int> std_list(3);
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Splice_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_2) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_3) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_3) {
  s21::list<int> my_list1;
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_4) {
  s21::list<int> my_list1;
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_5) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Insert_6) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.erase(my_list1.end().operator--());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.end().operator--());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_2) {
  s21::list<int> my_list1(5);
  my_list1.erase(my_list1.end().operator--());

  std::list<int> std_list1(5);
  std_list1.erase(std_list1.end().operator--());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

// // QUEUE

template <typename value_type>
bool compare_queues(s21::queue<value_type> my_queue,
                    std::queue<value_type> std_queue) {
  bool result = true;
  if (my_queue.size() == std_queue.size()) {
    while (!my_queue.empty() && !std_queue.empty()) {
      if (my_queue.front() != std_queue.front()) {
        result = false;
        break;
      }
      my_queue.pop();
      std_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(QueueTest, CompareQueues) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(20);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, CompareQueues_2) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(100);
  EXPECT_FALSE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.size(), 0);
  EXPECT_TRUE(my_queue.empty());
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, InitializerqueueConstructor) {
  s21::queue<int> my_queue{1, 2, 3, 7, 9};
  std::initializer_list<int> il = {1, 2, 3, 7, 9};
  std::queue<int> std_queue{il};
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, InitializerqueueConstructor_2) {
  std::initializer_list<int> b;
  s21::queue<int> my_queue{b};
  std::queue<int> std_queue{b};
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, InitializerqueueConstructor_3) {
  s21::queue<int> s21_queue = {1, 2, 3, 4};
  EXPECT_EQ(s21_queue.front(), 1);
  EXPECT_EQ(s21_queue.back(), 4);
  EXPECT_EQ(s21_queue.size(), size_t(4));
  EXPECT_EQ(s21_queue.empty(), false);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> my_queue{1, 2, 3, 7, 9};
  s21::queue<int> my_queue_copy(my_queue);
  std::initializer_list<int> il = {1, 2, 3, 7, 9};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, CopyConstructor_2) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2 = s21_queue_1;

  EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());
    s21_queue_1.pop(), s21_queue_2.pop();
  }
}

TEST(QueueTest, CopyConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> my_queue{1, 2, 3, 7, 20};
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move(std::move(my_queue));
  std::initializer_list<int> il = {1, 2, 3, 7, 20};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveConstructor_2) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2 = std::move(s21_queue_1);
  s21::queue<char> s21_queue_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  EXPECT_EQ(s21_queue_1.size(), size_t(0));
  EXPECT_EQ(s21_queue_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
}

TEST(QueueTest, MoveConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move(std::move(my_queue));
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> my_queue{1, 2, 3, 7, 20};
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move = std::move(my_queue);
  std::initializer_list<int> il = {1, 2, 3, 7, 20};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
}

TEST(QueueTest, MoveAssignmentOperatorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move = std::move(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
}

TEST(QueueTest, Front) {
  s21::queue<int> my_queue{99, 2, 3, 4, 5};
  std::initializer_list<int> il = {99, 1, 3, 7, 20};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.front(), std_queue.front());
}

TEST(QueueTest, Back) {
  s21::queue<int> my_queue{1, 2, 3, 3, 4, 99};
  std::initializer_list<int> il = {99, 1, 3, 5, 4, 7, 99};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.back(), std_queue.back());
}

TEST(QueueTest, Empty) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  my_queue.push(2354);
  std_queue.push(2354);
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueTest, Push) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  my_queue.push(627);
  std_queue.push(627);
  my_queue.push(2354);
  std_queue.push(2354);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, Push_2) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Pop) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{il};
  my_queue.pop();
  my_queue.pop();
  std_queue.pop();
  std_queue.pop();
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
  EXPECT_EQ(my_queue.front(), 3);
}

TEST(QueueTest, Pop_2) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  s21_queue.pop();
  s21_queue.pop();
  std_queue.pop();
  std_queue.pop();
  s21_queue.push(15);
  s21_queue.push(10);
  std_queue.push(15);
  std_queue.push(10);
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Swap) {
  s21::queue<int> my_queue1{1, 2, 3, 4, 5};
  s21::queue<int> my_queue2{6, 7, 8, 9, 10, 11};
  my_queue1.swap(my_queue2);

  std::initializer_list<int> il1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> il2 = {6, 7, 8, 9, 10, 11};
  std::queue<int> std_queue1{il1};
  std::queue<int> std_queue2{il2};
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(QueueTest, Swap_2) {
  s21::queue<int> my_queue1{1, 2, 99, 4, 242};
  s21::queue<int> my_queue2;
  my_queue1.swap(my_queue2);

  std::initializer_list<int> il = {1, 2, 99, 4, 242};
  std::queue<int> std_queue1{il};
  std::queue<int> std_queue2;
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(QueueTest, Swap_3) {
  s21::queue<std::string> s21_queue_1 = {"asdqwe123", "lgfjslsdfgj3",
                                         "qqqqwwwe", "431gtt4"};
  s21::queue<std::string> s21_queue_2 = {"pppppppppsw", "lolsdoallo",
                                         "iioiooioioioad"};
  s21::queue<std::string> s21_queue_3 = {"asdqwe123", "lgfjslsdfgj3",
                                         "qqqqwwwe", "431gtt4"};
  s21::queue<std::string> s21_queue_4 = {"pppppppppsw", "lolsdoallo",
                                         "iioiooioioioad"};

  s21_queue_1.swap(s21_queue_2);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_4.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
    s21_queue_1.pop(), s21_queue_4.pop();
  }
}

// SET

TEST(setTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(setTest, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(setTest, InitializerListConstructor_2) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(setTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(setTest, CopyConstructor_2) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  s21::set<char> s21_set_2 = s21_set_1;
  std::set<char> std_set_2 = std_set_1;

  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
  EXPECT_EQ(std_set_1.size(), std_set_2.size());
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(setTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(setTest, MoveConstructor_2) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd'};
  s21::set<char> s21_set_2 = std::move(s21_set_1);
  std::set<char> std_set_2 = std::move(std_set_1);

  EXPECT_EQ(s21_set_2.size(), std_set_2.size());
  EXPECT_EQ(s21_set_1.size(), std_set_1.size());
  EXPECT_EQ(s21_set_1.empty(), std_set_1.empty());
  auto it1 = s21_set_2.begin();
  auto it2 = std_set_2.begin();
  while (it1 != s21_set_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(setTest, Insert) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'c', 'd', 'b'};

  auto it = s21_set_1.begin();
  ++it;
  s21_set_1.insert('b');
  s21_set_1.insert('a');
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(setTest, Insert_2) {
  s21::set<char> s21_set;

  s21_set.insert('b');
  s21_set.insert('b');
  s21_set.insert('b');

  EXPECT_EQ(s21_set.size(), size_t(1));
}

TEST(setTest, Insert_3) {
  s21::set<float> s21_set;
  std::set<float> std_set;

  s21_set.insert(0.0000000000000000000000000000000000000000001);
  s21_set.insert(0.000000000000000000000000000000000000000000099);
  std_set.insert(0.0000000000000000000000000000000000000000001);
  std_set.insert(0.000000000000000000000000000000000000000000099);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(setTest, Insert_4) {
  s21::set<std::string> s21_set;
  std::set<std::string> std_set;
  s21_set.insert("asd");
  s21_set.insert("asa");
  s21_set.insert("asf");
  s21_set.insert("asg");
  s21_set.insert("ash");
  s21_set.insert("aqw");
  s21_set.insert("fgh");
  s21_set.insert("ghf");
  s21_set.insert("dghfg");
  s21_set.insert("dghfdsg");
  s21_set.insert("dghfgfsadfsd");
  s21_set.insert("dghfgfsadfsdasd");
  s21_set.insert("dghfgfsadfsasdasdd");
  s21_set.insert("dghfgfsadfsdasdasd");
  s21_set.insert("dghfgfdsasadfdsasasdsadsad");
  s21_set.insert("dghdsafgfsadfdsasasdsadsad");
  s21_set.insert("ådsdghfgfsadfdsasasdsadsad");
  s21_set.insert("dghfgfsadfdsasasdsaddsasad");
  s21_set.insert("dghfgfsadfdsasassadadsadsad");
  s21_set.insert("dghfgfsadfdsasdasasdsadsad");
  s21_set.insert("dghasdaasdfgfsadfsasdsadsad");
  s21_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  s21_set.insert("dghfgfsadfasdsasdsadsad");
  s21_set.insert("dghfgfsadfsasdsadsad");
  s21_set.insert("dghfgfsasdadfsasdsadsad");
  s21_set.insert("asdsadadghfgfsadfsasdsadsad");
  std_set.insert("asd");
  std_set.insert("asa");
  std_set.insert("asf");
  std_set.insert("asg");
  std_set.insert("ash");
  std_set.insert("aqw");
  std_set.insert("fgh");
  std_set.insert("ghf");
  std_set.insert("dghfg");
  std_set.insert("dghfdsg");
  std_set.insert("dghfgfsadfsd");
  std_set.insert("dghfgfsadfsdasd");
  std_set.insert("dghfgfsadfsasdasdd");
  std_set.insert("dghfgfsadfsdasdasd");
  std_set.insert("dghfgfdsasadfdsasasdsadsad");
  std_set.insert("dghdsafgfsadfdsasasdsadsad");
  std_set.insert("ådsdghfgfsadfdsasasdsadsad");
  std_set.insert("dghfgfsadfdsasasdsaddsasad");
  std_set.insert("dghfgfsadfdsasassadadsadsad");
  std_set.insert("dghfgfsadfdsasdasasdsadsad");
  std_set.insert("dghasdaasdfgfsadfsasdsadsad");
  std_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  std_set.insert("dghfgfsadfasdsasdsadsad");
  std_set.insert("dghfgfsadfsasdsadsad");
  std_set.insert("dghfgfsasdadfsasdsadsad");
  std_set.insert("asdsadadghfgfsadfsasdsadsad");
  for (auto i : std_set) {
    EXPECT_TRUE(s21_set.find(i) != s21_set.end());
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(setTest, BeginEnd) {
  s21::set<int> s{3, 5, 1, 4, 2};
  auto it = s.begin();
  ASSERT_EQ(*it, 1);

  s.clear();
  ASSERT_EQ(s.size(), 0);
}

TEST(setTest, SizeMaxSize) {
  s21::set<int> s{3, 5, 1, 4, 2};
  std::set<int> s1{3, 5, 1, 4, 2};
  ASSERT_EQ(s.size(), 5);
  ASSERT_GE(s.max_size(), s1.max_size());

  s.clear();
  ASSERT_EQ(s.size(), 0);
}
TEST(setTest, Erase) {
  s21::set<int> s{1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

TEST(setTest, Erase_2) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_set_2.begin();
  ++it;
  s21_set_2.erase(it);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(setTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(setTest, Swap_2) {
  s21::set<char> s21_set_1 = {'w', 'f', 'a', 's', 'a'};
  s21::set<char> s21_set_2 = {'b', 'e', 'w', 's', 'v', 'a', 'w'};
  s21::set<char> s21_set_3 = {'w', 'f', 'a', 's', 'a'};
  s21::set<char> s21_set_4 = {'b', 'e', 'w', 's', 'v', 'a', 'w'};
  s21_set_1.swap(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  auto it3 = s21_set_3.begin();
  auto it4 = s21_set_4.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_set_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_4.size());
  EXPECT_EQ(s21_set_2.size(), s21_set_3.size());
}

TEST(setTest, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s2.contains(3));
}

TEST(setTest, Merge_2) {
  s21::set<int> s21_set_1 = {1, 2, 3};
  s21::set<int> s21_set_2 = {3, 4, 5, 6};
  s21::set<int> s21_set_3 = {1, 2, 3, 4, 5, 6};
  s21_set_1.merge(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it3 = s21_set_3.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_3.size());
}

TEST(setTest, Contains) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  EXPECT_EQ(s21_set.contains(1), true);
  EXPECT_EQ(s21_set.contains(2), true);
  EXPECT_EQ(s21_set.contains(3), true);
  EXPECT_EQ(s21_set.contains(4), true);
  EXPECT_EQ(s21_set.contains(7), false);
  EXPECT_EQ(s21_set.contains(-2), false);
  EXPECT_EQ(s21_set.contains(0), false);
}

TEST(setTest, Find) {
  s21::set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
  auto it2 = s.find(4);
  EXPECT_EQ(it2, s.end());
}

TEST(setTest, Find_2) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  auto it_end = s21_set.end();
  EXPECT_EQ(*(s21_set.find(1)), 1);
  EXPECT_EQ(*(s21_set.find(3)), 3);
  EXPECT_EQ(*(s21_set.find(4)), 4);
  EXPECT_EQ(*(s21_set.find(2)), 2);
  EXPECT_EQ(s21_set.find(-4), it_end);
  EXPECT_EQ(s21_set.find(0), it_end);
  EXPECT_EQ(s21_set.find(120), it_end);
}

// MAP

TEST(mapTest, DefaultConstructor) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(mapTest, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_EQ(m.at(3), "three");
}

TEST(mapTest, InitializerListConstructor_2) {
  s21::map<int, std::string> s21_map = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  std::map<int, std::string> std_map = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(mapTest, CopyConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> copy_m(m);
  EXPECT_EQ(copy_m.size(), 3);
  EXPECT_FALSE(copy_m.empty());
  EXPECT_EQ(copy_m.at(1), "one");
}

TEST(mapTest, CopyConstructor_2) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  std::map<int, std::string> std_map_1 = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  s21::map<int, std::string> s21_map_2 = s21_map_1;
  std::map<int, std::string> std_map_2 = std_map_1;

  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
  EXPECT_EQ(std_map_1.size(), std_map_2.size());
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(mapTest, MoveConstructor) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  std::map<int, std::string> std_map_1 = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  s21::map<int, std::string> s21_map_2 = std::move(s21_map_1);
  std::map<int, std::string> std_map_2 = std::move(std_map_1);

  EXPECT_EQ(s21_map_2.size(), std_map_2.size());
  EXPECT_EQ(s21_map_1.size(), std_map_1.size());
  EXPECT_EQ(s21_map_1.empty(), std_map_1.empty());
  auto it1 = s21_map_2.begin();
  auto it2 = std_map_2.begin();
  while (it1 != s21_map_2.end()) {
    EXPECT_EQ(it1->first, it2->first);
    EXPECT_EQ(it1->second, it2->second);
    ++it1, ++it2;
  }
}

TEST(mapTest, Insert) {
  s21::map<int, std::string> map;
  map.insert(1, "one");
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(2, "two");
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(mapTest, Insert_2) {
  s21::map<int, std::string> map;
  map.insert(std::make_pair(1, "one"));
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  map.insert(std::make_pair(2, "two"));
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}
TEST(mapTest, Insert_3) {
  s21::map<int, std::string> map;
  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(it1->first, 1);
  EXPECT_EQ(it1->second, "one");
  auto [it2, inserted2] = map.insert_or_assign(1, "ONE");
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(it2->first, 1);
  EXPECT_EQ(it2->second, "ONE");
  map.insert_or_assign(2, "two");
  map.insert_or_assign(3, "three");
  map.insert_or_assign(4, "four");
  map.insert_or_assign(5, "five");
  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}

TEST(mapTest, Insert_4) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 322},
      {'a', 5},
  };

  EXPECT_EQ(s21_map_1.insert('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert('d', 14).second, false);

  std::pair<char, int> pair1('a', 5);
  std::pair<char, int> pair2('a', 28);

  EXPECT_EQ(s21_map_1.insert(pair1).second, true);
  EXPECT_EQ(s21_map_1.insert(pair2).second, false);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(mapTest, Insert_5) {
  s21::map<std::string, int> s21_map;
  s21_map.insert("asd", 0);
  s21_map.insert("asa", 1);
  s21_map.insert("asf", 2);
  s21_map.insert("asg", 3);
  s21_map.insert("ash", 4);
  s21_map.insert("aqw", 5);
  s21_map.insert("fgh", 6);
  s21_map.insert("ghf", 7);
  s21_map.insert("dghfg", 8);
  s21_map.insert("dghfdsg", 9);
  s21_map.insert("dghfgfsadfsd", 10);
  s21_map.insert("dghfgfsadfsdasd", 11);
  s21_map.insert("dghfgfsadfsasdasdd", 12);
  s21_map.insert("dghfgfsadfsdasdasd", 13);
  s21_map.insert("dghfgfdsasadfdsasasdsadsad", 14);
  s21_map.insert("dghdsafgfsadfdsasasdsadsad", 15);
  s21_map.insert("ådsdghfgfsadfdsasasdsadsad", 16);
  s21_map.insert("dghfgfsadfdsasasdsaddsasad", 17);
  s21_map.insert("dghfgfsadfdsasassadadsadsad", 18);
  s21_map.insert("dghfgfsadfdsasdasasdsadsad", 19);
  s21_map.insert("dghasdaasdfgfsadfsasdsadsad", 20);
  s21_map.insert("asddghfgfsadfsasaß∂asdsadsad", 21);
  s21_map.insert("dghfgfsadfasdsasdsadsad", 22);
  s21_map.insert("dghfgfsadfsasdsadsad", 23);
  s21_map.insert("dghfgfsasdadfsasdsadsad", 24);
  s21_map.insert("asdsadadghfgfsadfsasdsadsad", 25);
  std::map<std::string, int> std_map;
  std_map.insert(std::pair<std::string, int>("asd", 0));
  std_map.insert(std::pair<std::string, int>("asa", 1));
  std_map.insert(std::pair<std::string, int>("asf", 2));
  std_map.insert(std::pair<std::string, int>("asg", 3));
  std_map.insert(std::pair<std::string, int>("ash", 4));
  std_map.insert(std::pair<std::string, int>("aqw", 5));
  std_map.insert(std::pair<std::string, int>("fgh", 6));
  std_map.insert(std::pair<std::string, int>("ghf", 7));
  std_map.insert(std::pair<std::string, int>("dghfg", 8));
  std_map.insert(std::pair<std::string, int>("dghfdsg", 9));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsd", 10));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasd", 11));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdasdd", 12));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasdasd", 13));
  std_map.insert(std::pair<std::string, int>("dghfgfdsasadfdsasasdsadsad", 14));
  std_map.insert(std::pair<std::string, int>("dghdsafgfsadfdsasasdsadsad", 15));
  std_map.insert(std::pair<std::string, int>("ådsdghfgfsadfdsasasdsadsad", 16));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasasdsaddsasad", 17));
  std_map.insert(
      std::pair<std::string, int>("dghfgfsadfdsasassadadsadsad", 18));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasdasasdsadsad", 19));
  std_map.insert(
      std::pair<std::string, int>("dghasdaasdfgfsadfsasdsadsad", 20));
  std_map.insert(
      std::pair<std::string, int>("asddghfgfsadfsasaß∂asdsadsad", 21));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfasdsasdsadsad", 22));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdsadsad", 23));
  std_map.insert(std::pair<std::string, int>("dghfgfsasdadfsasdsadsad", 24));
  std_map.insert(
      std::pair<std::string, int>("asdsadadghfgfsadfsasdsadsad", 25));
  for (auto i : std_map) {
    EXPECT_EQ(i.second, s21_map[i.first]);
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(mapTest, Insert_6) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 14},
      {'a', 28},
  };

  EXPECT_EQ(s21_map_1.insert_or_assign('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('d', 14).second, false);

  EXPECT_EQ(s21_map_1.insert_or_assign('a', 5).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('a', 28).second, false);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(mapTest, AtAndOperatorBrackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::out_of_range);
  map[4] = "four";
  EXPECT_EQ(map[4], "four");
  map[2] = "TWO";
  EXPECT_EQ(map[2], "TWO");
}

TEST(mapTest, AtAndOperatorBrackets_2) {
  s21::map<std::string, int> m;
  m["123"] = 5;
  EXPECT_EQ(5, m["123"]);
}

TEST(mapTest, EmptyAndSize) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), 0);
  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

TEST(mapTest, MaxSize) {
  s21::map<int, std::string> map;
  std::map<int, std::string> map1;

  EXPECT_GT(map.max_size(), map1.max_size());
}
TEST(mapTest, Erase) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});

  auto it1 = map.begin()++;
  map.erase(it1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(1));
}

TEST(mapTest, Erase_2) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  s21::map<int, std::string> s21_map_2 = {
      {1, "asdqwe123"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  auto it = s21_map_1.begin();
  ++it;
  s21_map_1.erase(it);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(mapTest, Erase_3) {
  std::pair<int, int> pair1{10, 10};
  std::pair<int, int> pair2{5, 5};
  std::pair<int, int> pair3{15, 15};
  std::pair<int, int> pair4{4, 4};
  std::pair<int, int> pair5{18, 18};
  std::pair<int, int> pair6{13, 13};
  std::pair<int, int> pair7{16, 16};

  s21::map<int, int> s21_map = {pair1, pair2, pair3, pair4,
                                pair5, pair6, pair7};

  auto it = s21_map.begin();
  it++;
  it++;
  it++;
  it++;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 4);
  EXPECT_EQ(s21_map.end().operator--()->first, 18);
  EXPECT_EQ(s21_map.size(), 6U);

  it = s21_map.begin();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.end().operator--()->first, 18);
  EXPECT_EQ(s21_map.size(), 5U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.end().operator--()->first, 18);
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.end().operator--();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.begin()->first, 5);
  EXPECT_EQ(s21_map.end().operator--()->first, 16);
  EXPECT_EQ(s21_map.size(), 3U);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  it++;
  s21_map.erase(it);

  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0);
}

TEST(mapTest, Erase_4) {
  std::pair<int, int> pair1{30, 30};
  std::pair<int, int> pair2{1543, 1543};

  s21::map<int, int> s21_map = {pair1, pair2};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  s21_map.erase(it);

  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(mapTest, Erase_5) {
  std::pair<std::string, int> pair1{"hello", 1};
  std::pair<std::string, int> pair2{"hi", 2};
  std::pair<std::string, int> pair3{"hola-hola", 2};
  std::pair<std::string, int> pair4{"hola", 3};
  std::pair<std::string, int> pair5{"hello, there", 1};

  s21::map<std::string, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.end().operator--();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.end().operator--()->first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);
  it = s21_map.end().operator--();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.end().operator--()->first, "hi");
  EXPECT_EQ(s21_map.size(), 3U);

  s21_map.insert(pair3);
  s21_map.insert(pair4);
  it = s21_map.end().operator--();
  s21_map.erase(it);
  EXPECT_EQ(s21_map.end().operator--()->first, "hola");
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(mapTest, Erase_6) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{12.4457, 2};
  std::pair<double, int> pair3{56.84, 2};
  std::pair<double, int> pair4{941.44, 3};
  std::pair<double, int> pair5{44.48, 1};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.end().operator--();
  it--;
  s21_map.erase(it);
  it = s21_map.end().operator--();
  EXPECT_EQ(it->first, 941.44);
  EXPECT_EQ(s21_map.size(), 4U);

  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(s21_map.end().operator--()->first, 44.48);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(mapTest, Erase_7) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  auto it = s21_map.begin();
  --it;
  --it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  EXPECT_EQ(it->first, 22.2);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(mapTest, Erase_8) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{6.84, 2};
  std::pair<double, int> pair5{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(it->first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(mapTest, Erase_9) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{12.4457, 2};
  std::pair<double, int> pair3{56.84, 2};
  std::pair<double, int> pair4{941.44, 3};
  std::pair<double, int> pair5{44.48, 1};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4, pair5};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ(it->first, 44.48);
  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(mapTest, Erase_10) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{1.44, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4};

  auto it = s21_map.begin();
  ++it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  EXPECT_EQ(it->first, 22.2);
  EXPECT_EQ(s21_map.size(), 3U);
}

TEST(mapTest, Erase_11) {
  std::pair<double, int> pair1{22.2, 1};
  std::pair<double, int> pair2{44.48, 1};
  std::pair<double, int> pair3{12.4457, 2};
  std::pair<double, int> pair4{32.45, 2};
  std::pair<double, int> pair5{65.12, 3};
  std::pair<double, int> pair6{66.32, 3};
  std::pair<double, int> pair7{40.54, 3};
  std::pair<double, int> pair8{6.4, 3};

  s21::map<double, int> s21_map = {pair1, pair2, pair3, pair4,
                                   pair5, pair6, pair7, pair8};

  auto it = s21_map.end().operator--();
  --it;
  --it;
  --it;
  --it;
  s21_map.erase(it);
  it = s21_map.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(it->first, 40.54);
  EXPECT_EQ(s21_map.size(), 7U);
}

TEST(mapTest, Erase_12) {
  std::pair<double, int> pair1{22.2, 1};

  s21::map<double, int> s21_map = {pair1};

  auto it = s21_map.end().operator--();
  --it;
  ++it;
  s21_map.erase(it);
  EXPECT_EQ(s21_map.size(), 0U);
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.swap(map2);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));

  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(mapTest, Swap_2) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  s21::map<int, std::string> s21_map_2 = {{10, "pppppppppsw"},
                                          {12, "lolsdoallo"},
                                          {13, "iioiooioioioad"},
                                          {14, "pasdgpsdg"}};
  s21::map<int, std::string> s21_map_3 = {
      {1, "asdqwe123"}, {2, "lgfjslsdfgj3"}, {3, "qqqqwwwe"}, {4, "431gtt4"}};
  s21::map<int, std::string> s21_map_4 = {{10, "pppppppppsw"},
                                          {12, "lolsdoallo"},
                                          {13, "iioiooioioioad"},
                                          {14, "pasdgpsdg"}};

  s21_map_1.swap(s21_map_2);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  auto it3 = s21_map_3.begin();
  auto it4 = s21_map_4.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_map_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_4.size());
  EXPECT_EQ(s21_map_2.size(), s21_map_3.size());
}

TEST(mapTest, Merge) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
}

TEST(mapTest, Contains) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

TEST(mapTest, Contains_2) {
  s21::map<int, std::string> s21_map;
  s21_map.insert(1, "sasasadsdas");
  s21_map.insert(2, "cvbvcbcv");
  s21_map.insert(3, "dflgkjl33");
  s21_map.insert(4, "rrrqrqrqr");
  EXPECT_EQ(s21_map.contains(1), true);
  EXPECT_EQ(s21_map.contains(2), true);
  EXPECT_EQ(s21_map.contains(3), true);
  EXPECT_EQ(s21_map.contains(4), true);
  EXPECT_EQ(s21_map.contains(7), false);
  EXPECT_EQ(s21_map.contains(-2), false);
  EXPECT_EQ(s21_map.contains(0), false);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}