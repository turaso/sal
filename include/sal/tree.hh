#ifndef SAL_TREE_HH_
#define SAL_TREE_HH_

#include <concepts>
#include <initializer_list>
#include <typeinfo>
#include <vector>
#include <stack>

namespace sal {

template <template <typename, typename...> class Algorithm,
          typename Data, typename... Args>
concept TreeAlgorithm = requires(Algorithm<Data, Args...> a, Data d) {
  { a.insert(d) };
  { a.remove(d) };
  { a.find(d) };
};

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
class Tree {
public:
  using data_type = Data;
  using tree_type = Algorithm<data_type>;
  constexpr Tree() = default;
  constexpr Tree(std::initializer_list<data_type>&&);
  constexpr bool insert(const data_type&);
  constexpr bool insert(data_type&&);
  constexpr bool remove(const data_type&);
  constexpr bool remove(data_type&&);
  constexpr bool find(const data_type&) const;
  constexpr bool find(data_type&&) const;
  constexpr std::size_t size() const;
  constexpr bool empty() const;
  constexpr std::vector<typename tree_type::value_type> bfs() const;
  template <typename T>
  requires std::convertible_to<
      std::remove_cv_t<std::remove_reference_t<T>>,
      data_type
  > constexpr Tree operator+(T&&) const;
  constexpr Tree operator+(const Tree&) const;
  constexpr Tree operator+(Tree&&) const;
  constexpr Tree operator+(std::initializer_list<data_type>&&) const;
  /// !! operator-
  virtual ~Tree() = default;
protected:
  tree_type algo_;
  std::size_t size_ = 0;
private:
};

} /// namespace sal

namespace sal {

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr Tree<Data, Algorithm>::Tree(std::initializer_list<data_type>&& list) {
  for (auto&& e : list) {
    this->insert(e);
  }
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr bool Tree<Data, Algorithm>::insert(const data_type& d) {
  if (!this->find(d)) {
    this->algo_.insert(d);
    this->size_++;
    return true;
  }
  return false;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr bool Tree<Data, Algorithm>::insert(data_type&& d) {
  if (!this->find(d)) {
    this->algo_.insert(d);
    this->size_++;
    return true;
  }
  return false;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr bool Tree<Data, Algorithm>::remove(const data_type& d) {
  if (this->find(d)) {
    this->algo_.remove(d);
    this->size_--;
    return true;
  }
  return false;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr bool Tree<Data, Algorithm>::remove(data_type&& d) {
  if (this->find(d)) {
    this->algo_.remove(d);
    this->size_--;
    return true;
  }
  return false;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr bool Tree<Data, Algorithm>::find(const data_type& d) const {
  return static_cast<bool>(this->algo_.find(d));
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr bool Tree<Data, Algorithm>::find(data_type&& d) const {
  return static_cast<bool>(this->algo_.find(d));
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr std::size_t Tree<Data, Algorithm>::size() const {
  return this->size_;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr bool Tree<Data, Algorithm>::empty() const {
  return this->size_ == 0;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
constexpr std::vector<typename Tree<Data, Algorithm>::tree_type::value_type>
Tree<Data, Algorithm>::bfs() const {
  std::vector<typename Tree<Data, Algorithm>::tree_type::value_type> ret;
  /// ?? to be improved
  std::stack<const typename Tree<Data, Algorithm>::tree_type::Node*> stack;
  stack.push(this->algo_.root());
  while (!stack.empty()) {
    const auto* top = stack.top();
    stack.pop();
    ret.push_back(top->value());
    for (const auto* child : top->childs()) {
      if (child) {
        stack.push(child);
      }
    }
  }
  return ret;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data>
template <typename T>
requires std::convertible_to<
    std::remove_cv_t<std::remove_reference_t<T>>,
    typename Tree<Data, Algorithm>::data_type
> constexpr Tree<Data, Algorithm>
Tree<Data, Algorithm>::operator+(
    T&& data /// !! to be checked
) const {
  Tree other = *this;
  other.insert(static_cast<data_type>(data));
  return other;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data> constexpr Tree<Data, Algorithm>
Tree<Data, Algorithm>::operator+(const Tree& other) const {
  Tree tree;
  Tree const * smaller = nullptr;
  if (this->size() >= other.size()) {
    tree = Tree(*this);
    smaller = &other;
  } else {
    tree = Tree(other);
    smaller = this;
  }
  for (auto&& val : smaller->bfs()) {
    tree.insert(val);
  }
  return tree;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data> constexpr Tree<Data, Algorithm>
Tree<Data, Algorithm>::operator+(Tree&& other) const {
  for (auto&& val : this->bfs()) {
    other.insert(val);
  }
  return other;
}

template <typename Data, template <typename, typename...> class Algorithm>
requires TreeAlgorithm<Algorithm, Data> constexpr Tree<Data, Algorithm>
Tree<Data, Algorithm>::operator+(
    std::initializer_list<Tree::data_type>&& list
) const {
  Tree tree(*this);
  for (auto&& val : list) {
    tree.insert(val);
  }
  return tree;
}

} /// namespace sal

#endif /// SAL_TREE_HH_
