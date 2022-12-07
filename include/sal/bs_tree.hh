#ifndef SAL_BS_TREE_HH_
#define SAL_BS_TREE_HH_

#include <sal/xx_tree_base.hh>

namespace sal {

namespace bs {

template <NodeValue T>
class Node : public NodeTreeBinaryBase<Node, T> {
public:
  using value_type = T;
  using node_type = Node<T>;
  constexpr Node() = default;
  constexpr Node(value_type v);
  constexpr Node(value_type v, node_type* p);
  constexpr Node(const Node&) = default;
  constexpr Node& operator=(const Node&) = default;
  constexpr Node(Node&&) = default;
  constexpr Node& operator=(Node&&) = default;
  constexpr node_type* const & parent() const;
  constexpr node_type* & parent();
  constexpr virtual ~Node() = default;
protected:
  node_type* parent_ = nullptr;
private:
};

template <NodeValue T>
constexpr Node<T>::Node(value_type v) {
  this->value() = v;
}

template <NodeValue T>
constexpr Node<T>::Node(value_type v, node_type* p) : parent_(p) {
  this->value() = v;
}

template <NodeValue T>
constexpr typename Node<T>::node_type* const & Node<T>::parent() const {
  return this->parent_;
}

template <NodeValue T>
constexpr typename Node<T>::node_type* & Node<T>::parent() {
  return this->parent_;
}

} /// namespace bs

namespace info {

template <typename Data>
class BSTree {
public:
  using value_type = Data;
  using node_type = bs::Node<value_type>;
};

} /// namespace info

template <typename Data>
class BSTree : public XXTreeBase<typename info::BSTree<Data>::node_type> {
public:
  using value_type = typename info::BSTree<Data>::value_type;
  using node_type = typename info::BSTree<Data>::node_type;
  using XXTreeBase<typename info::BSTree<Data>::node_type>::insert;
  using XXTreeBase<typename info::BSTree<Data>::node_type>::remove;
  using XXTreeBase<typename info::BSTree<Data>::node_type>::find;
  using XXTreeBase<typename info::BSTree<Data>::node_type>::root;
  constexpr BSTree() = default;
  constexpr BSTree(const BSTree&);
  constexpr BSTree& operator=(const BSTree&);
  constexpr BSTree(BSTree&&);
  constexpr BSTree& operator=(BSTree&&);
  constexpr virtual ~BSTree() = default;
//  constexpr node_type* insert(value_type&& v) { return XXTreeBase<typename info::BSTree<Data>::node_type>::insert(v); };
protected:
  constexpr node_type*
      insert(const value_type&, node_type*&, node_type* p = nullptr) override;
  constexpr node_type*
      remove(const value_type&, node_type*&) override;
  constexpr node_type*
      find(const value_type&, node_type* const &) const override;
private:
};

} /// namespace sal

namespace sal {

template <typename Data>
constexpr BSTree<Data>::BSTree(const BSTree& o) : XXTreeBase<node_type>(o) {}

template <typename Data>
constexpr BSTree<Data>& BSTree<Data>::operator=(const BSTree& o) {
  return XXTreeBase<node_type>::operator=(o);
}

template <typename Data>
constexpr BSTree<Data>::BSTree(BSTree&& o) : XXTreeBase<node_type>(o) {}

template <typename Data>
constexpr BSTree<Data>& BSTree<Data>::operator=(BSTree&& o) {
  return XXTreeBase<node_type>::operator=(std::move(o));
}

template <typename Data>
constexpr typename BSTree<Data>::node_type*
BSTree<Data>::insert(const value_type& v, node_type*& n, node_type* p) {
  if (n == nullptr) {
    return n = new node_type(v, p);
  } else if (v < n->value()) {
    return this->insert(v, n->left(), n);
  } else if (v > n->value()) {
    return this->insert(v, n->right(), n);
  } else {
    return nullptr;
  }
}

template <typename Data>
constexpr typename BSTree<Data>::node_type*
BSTree<Data>::remove(const value_type& v, node_type*& n) {
  if (n == nullptr) {
    return nullptr;
  } else if (v < n->value()) {
    return this->remove(v, n->left());
  } else if (v > n->value()) {
    return this->remove(v, n->right());
  } else {
    if (n->left() == nullptr && n->right() == nullptr) {
      delete n;
      n = nullptr;
    } else if (n->left() == nullptr) {
      auto* toBeDeleted = n;
      n = n->right();
      toBeDeleted->right() = nullptr;
      delete toBeDeleted;
    } else if (n->right() == nullptr) {
      auto* toBeDeleted = n;
      n = n->left();
      toBeDeleted->left() = nullptr;
      delete toBeDeleted;
    } else {
      auto* predecessor = this->predecessor(n);
      if (predecessor == n->left()) {
        n->left() = nullptr;
        predecessor->right() = n->right();
        n->right() = nullptr;
      } else {
        predecessor->parent()->right() = predecessor->left();
        predecessor->left() = n->left();
        n->left() = nullptr;
        predecessor->right() = n->right();
        n->right() = nullptr;
      }
      const auto* toBeDeleted = n;
      delete toBeDeleted;
      n = predecessor;
    }
    return n;
  }
}

template <typename Data>
constexpr typename BSTree<Data>::node_type*
BSTree<Data>::find(const value_type& v, node_type* const & n) const {
  if (n == nullptr) {
    return nullptr;
  } else if (v < n->value()) {
    return this->find(v, n->left());
  } else if (v > n->value()) {
    return this->find(v, n->right());
  } else {
    return n;
  }
}

}

#endif /// SAL_BS_TREE_HH_
