#ifndef SAL_XX_TREE_BASE_HH_
#define SAL_XX_TREE_BASE_HH_

#include <concepts>

#include <sal/node_tree_binary_base.hh>
#include <sal/util.hh>

namespace sal {

template <typename T>
concept Nodeable = requires (T o) {
  typename decltype(o)::value_type;
};

template <Nodeable Node>
class XXTreeBase {
public:
  using node_type = Node;
  using value_type = typename node_type::value_type;
  constexpr XXTreeBase() = default;
  constexpr XXTreeBase(const XXTreeBase&);
  constexpr XXTreeBase& operator=(const XXTreeBase&);
  constexpr XXTreeBase(XXTreeBase&&);
  constexpr XXTreeBase& operator=(XXTreeBase&&);
  constexpr node_type* const & root() const;
  constexpr node_type* insert(const value_type&);
  constexpr node_type* insert(value_type&&);
  constexpr node_type* remove(const value_type&);
  constexpr node_type* remove(value_type&&);
  constexpr node_type* find(const value_type&) const;
  constexpr node_type* find(value_type&&) const;
  constexpr virtual ~XXTreeBase();
protected:
  constexpr node_type*& root();
  constexpr node_type* successor(node_type*) const;
  constexpr node_type* successor(node_type*);
  constexpr node_type* predecessor(node_type*) const;
  constexpr node_type* predecessor(node_type*);
  constexpr virtual node_type*
      insert(const value_type&, node_type*&, node_type* p = nullptr) = 0;
  constexpr virtual node_type*
      remove(const value_type&, node_type*&) = 0;
  constexpr virtual node_type*
      find(const value_type&, node_type* const &) const = 0;
  node_type* root_ = nullptr;
private:
};

} /// namespace sal

namespace sal {

template <Nodeable Node>
constexpr XXTreeBase<Node>::XXTreeBase(const XXTreeBase& other) {
  if (other.root()) {
    this->root() = new Node(*other.root());
  }
}

template <Nodeable Node>
constexpr XXTreeBase<Node>& XXTreeBase<Node>::operator=(const XXTreeBase& other) {
  if (this != &other) {
    if (other.root()) {
      this->root() = new Node(*other.root());
    }
  }
  return *this;
}

template <Nodeable Node>
constexpr XXTreeBase<Node>::XXTreeBase(XXTreeBase&& other) {
  if (other.root()) {
    this->root() = new Node(std::move(*other.root()));
    other.root() = nullptr;
  }
}

template <Nodeable Node>
constexpr XXTreeBase<Node>& XXTreeBase<Node>::operator=(XXTreeBase&& other) {
  if (this != &other) {
    if (other.root()) {
      this->root() = new Node(std::move(*other.root()));
      other.root() = nullptr;
    }
  }
  return *this;
}

/*!
 * @note node->right() != nullptr
 */
template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::successor(node_type* node) const {
  auto* ret = node->right();
  while (ret->left()) {
    ret = ret->left();
  }
  return ret;
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::successor(node_type* node) {
  return util::as_mutable(std::as_const(*this).successor(node));
}

/*!
 * @note node->left() != nullptr
 */
template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::predecessor(node_type* node) const {
  auto* ret = node->left();
  while (ret->right()) {
    ret = ret->right();
  }
  return ret;
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::predecessor(node_type* node) {
  return util::as_mutable(std::as_const(*this).predecessor(node));
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type* const &
XXTreeBase<Node>::root() const {
  return this->root_;
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*&
XXTreeBase<Node>::root() {
  return this->root_;
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::insert(const typename XXTreeBase<Node>::value_type& val) {
  return this->insert(val, this->root());
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::insert(typename XXTreeBase<Node>::value_type&& val) {
  return this->insert(val, this->root());
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::remove(const typename XXTreeBase<Node>::value_type& val) {
  return this->remove(val, this->root());
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::remove(typename XXTreeBase<Node>::value_type&& val) {
  return this->remove(val, this->root());
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::find(const typename XXTreeBase<Node>::value_type& val) const {
  return this->find(val, this->root());
}

template <Nodeable Node>
constexpr typename XXTreeBase<Node>::node_type*
XXTreeBase<Node>::find(typename XXTreeBase<Node>::value_type&& val) const {
  return this->find(val, this->root());
}

template <Nodeable Node>
constexpr XXTreeBase<Node>::~XXTreeBase() {
  if (this->root()) {
    delete this->root();
  }
}

} /// namespace sal

#endif // SAL_XX_TREE_BASE_HH_
