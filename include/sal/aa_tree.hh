#ifndef SAL_AA_TREE_HH_
#define SAL_AA_TREE_HH_

#include <algorithm>
#include <cstddef>
#include <utility>

#include <sal/node_tree_binary_base.hh>

namespace sal {

template <typename Data>
class AATree {
public:
  using value_type = Data;
  template <NodeValue T>
  class Node : public NodeTreeBinaryBase<Node, T> {
  public:
    constexpr Node() = default;
    constexpr Node(T);
    constexpr Node(const Node&) = default;
    constexpr Node& operator=(const Node&) = default;
    constexpr Node(Node&&) = default;
    constexpr Node& operator=(Node&&) = default;
    constexpr const std::size_t& level() const;
    constexpr std::size_t& level();
    constexpr virtual ~Node() = default;
  protected:
    std::size_t level_ = 0;
  private:
  };
  using node_type = Node<value_type>;
  constexpr AATree() = default;
  constexpr AATree(const AATree&);
  constexpr AATree& operator=(const AATree&);
  constexpr AATree(AATree&&);
  constexpr AATree& operator=(AATree&&);
  constexpr node_type* const & root() const;
  constexpr node_type*& root();
  constexpr node_type* insert(const value_type&);
  constexpr node_type* insert(value_type&&);
  constexpr node_type* remove(const value_type&);
  constexpr node_type* remove(value_type&&);
  constexpr node_type* find(const value_type&) const;
  constexpr node_type* find(value_type&&) const;
  constexpr virtual ~AATree();
protected:
  constexpr static node_type* successor(node_type*);
  constexpr static node_type* predecessor(node_type*);
  constexpr static node_type* decrease(node_type*);
  constexpr node_type*& skew(node_type*&);
  constexpr node_type*& split(node_type*&);
  constexpr node_type* insert(const value_type&, node_type*&);
  constexpr node_type* remove(const value_type&, node_type*&);
  constexpr node_type* find(const value_type&, node_type* const &) const;
  node_type* root_ = nullptr;
private:
};

} /// namespace sal

namespace sal {

template <typename Data>
template <NodeValue T>
constexpr AATree<Data>::Node<T>::Node(T value)
  : NodeTreeBinaryBase<Node, T>(value) {}

template <typename Data>
template <NodeValue T>
constexpr const std::size_t& AATree<Data>::Node<T>::level() const {
  return this->level_;
}

template <typename Data>
template <NodeValue T>
constexpr std::size_t& AATree<Data>::Node<T>::level() { return this->level_; }

template <typename Data>
constexpr AATree<Data>::AATree(const AATree& other) {
  if (other.root()) {
    this->root() = new Node(*other.root());
  }
}

template <typename Data>
constexpr AATree<Data>& AATree<Data>::operator=(const AATree& other) {
  if (this != &other) {
    if (other.root()) {
      this->root() = new Node(*other.root());
    }
  }
  return *this;
}

template <typename Data>
constexpr AATree<Data>::AATree(AATree&& other) {
  if (other.root()) {
    this->root() = new Node(std::move(*other.root()));
    other.root() = nullptr;
  }
}

template <typename Data>
constexpr AATree<Data>& AATree<Data>::operator=(AATree&& other) {
  if (this != &other) {
    if (other.root()) {
      this->root() = new Node(std::move(*other.root()));
      other.root() = nullptr;
    }
  }
  return *this;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*&
AATree<Data>::skew(AATree<Data>::node_type*& node) {
  if (!node) {
    return node;
  } else if (!node->left()) {
    return node;
  } else if (node->left()->level() == node->level()) {
    auto* l = node->left();
    node->left() = l->right();
    l->right() = node;
    node = l;
  }
  return node;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*&
AATree<Data>::split(AATree<Data>::node_type*& node) {
  if (!node) {
    return node;
  } else if (!node->right() || !node->right()->right()) {
    return node;
  } else if (node->level() == node->right()->right()->level()) {
    auto* r = node->right();
    node->right() = r->left();
    r->left() = node;
    r->level()++;
    node = r;
  }
  return node;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::successor(node_type* node) {
  auto* ret = node->right();
  while (ret->left()) {
    ret = ret->left();
  }
  return ret;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::predecessor(node_type* node) {
  auto* ret = node->left();
  while (ret->right()) {
    ret = ret->right();
  }
  return ret;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::decrease(node_type* node) {
  if (node->left() && node->right()) {
    const auto should =
        std::min(node->left()->level(), node->right()->level()) + 1;
    if (should < node->level()) {
      node->level() = should;
      if (node->right() && should < node->right()->level()) {
        node->right()->level() = should;
      }
    }
  }
  return node;
}

template <typename Data>
constexpr typename AATree<Data>::node_type* const &
AATree<Data>::root() const {
  return this->root_;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*&
AATree<Data>::root() {
  return this->root_;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::insert(
    const typename AATree<Data>::value_type& val,
    AATree<Data>::node_type*& node
) {
  if (!node) {
    node = new Node(val);
  } else if (val <= node->value()) {
    node->left() = this->insert(val, node->left());
  } else {
    node->right() = this->insert(val, node->right());
  }
  return this->split(this->skew(node));
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::remove(
    const typename AATree<Data>::value_type& val,
    AATree<Data>::node_type*& node
) {
  if (!node) {
    return node;
  } else if (val > node->value()) {
    node->right() = this->remove(val, node->right());
  } else if (val < node->value()) {
    node->left() = this->remove(val, node->left());
  } else {
    if (!node->left() && !node->right()) {
      delete node;
      if (node == this->root()) {
        this->root() = nullptr;
      }
      return nullptr;
    } else if (!node->left()) {
      auto* l = this->successor(node);
      node->value() = l->value();
      node->right() = this->remove(l->value(), node->right());
    } else {
      auto* l = this->predecessor(node);
      node->value() = l->value();
      node->left() = this->remove(l->value(), node->left());
    }
  }
  node = this->decrease(node);
  node = this->skew(node);
  if (node) {
    node->right() = this->skew(node->right());
  }
  if (node->right()) {
    node->right()->right() = this->skew(node->right()->right());
  }
  node = this->split(node);
  if (node) {
    node->right() = this->split(node->right());
  }
  return node;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::find(
    const typename AATree<Data>::value_type& val,
    AATree<Data>::node_type* const & node
) const {
  if (!node) {
    return node;
  } else if (val > node->value()) {
    return this->find(val, node->right());
  } else if (val < node->value()) {
    return this->find(val, node->left());
  }
  return node;
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::insert(const typename AATree<Data>::value_type& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::insert(typename AATree<Data>::value_type&& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::remove(const typename AATree<Data>::value_type& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::remove(typename AATree<Data>::value_type&& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::find(const typename AATree<Data>::value_type& val) const {
  return this->find(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::node_type*
AATree<Data>::find(typename AATree<Data>::value_type&& val) const {
  return this->find(val, this->root());
}

template <typename Data>
constexpr AATree<Data>::~AATree() {
  if (this->root()) {
    delete this->root();
  }
}

} /// namespace sal

#endif /// SAL_AA_TREE_HH_
