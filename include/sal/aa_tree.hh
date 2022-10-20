#ifndef SAL_AA_TREE_HH_
#define SAL_AA_TREE_HH_

#include <algorithm>
#include <cstddef>
#include <utility>

namespace sal {

template <typename Data>
class AATree {
public:
  using value_type = Data;
  class Node {
  public:
    static constexpr std::size_t CHILDS_NUM = 2;
    template <typename T>
    using container_type = T[CHILDS_NUM];
    using childs_type = container_type<Node*>;
    constexpr Node() = default;
    constexpr Node(value_type);
    constexpr Node(const Node&);
    constexpr Node& operator=(const Node&);
    constexpr Node(Node&&);
    constexpr Node& operator=(Node&&);
    constexpr const value_type& value() const;
    constexpr value_type& value();
    constexpr const std::size_t& level() const;
    constexpr std::size_t& level();
    constexpr const childs_type& childs() const;
    constexpr childs_type& childs();
    constexpr const Node*& left() const;
    constexpr Node*& left();
    constexpr const Node*& right() const;
    constexpr Node*& right();
    constexpr virtual ~Node();
  protected:
    std::size_t level_ = 0;
    childs_type childs_{nullptr};
    value_type value_{};
  private:
  };
  constexpr AATree() = default;
  constexpr AATree(const AATree&);
  constexpr AATree& operator=(const AATree&);
  constexpr AATree(AATree&&);
  constexpr AATree& operator=(AATree&&);
  constexpr Node* const & root() const;
  constexpr Node*& root();
  constexpr Node* insert(const value_type&);
  constexpr Node* insert(value_type&&);
  constexpr Node* remove(const value_type&);
  constexpr Node* remove(value_type&&);
  constexpr Node* find(const value_type&) const;
  constexpr Node* find(value_type&&) const;
  constexpr virtual ~AATree();
protected:
  constexpr static Node* successor(Node*);
  constexpr static Node* predecessor(Node*);
  constexpr static Node* decrease(Node*);
  constexpr Node*& skew(Node*&);
  constexpr Node*& split(Node*&);
  constexpr Node* insert(const value_type&, Node*&);
  constexpr Node* remove(const value_type&, Node*&);
  constexpr Node* find(const value_type&, Node* const &) const;
  Node* root_ = nullptr;
private:
};

} /// namespace sal

namespace sal {

template <typename Data>
constexpr AATree<Data>::Node::Node(AATree<Data>::value_type value)
  : value_(value) {}

template <typename Data>
constexpr AATree<Data>::Node::Node(const Node& other)
  : level_(other.level()),
    childs_(nullptr),
    value_(other.value()) {
  for (auto i = 0u; i < other.CHILDS_NUM; i++) {
    if (other.childs()[i]) {
      this->childs()[i] = new Node(*other.childs()[i]);
    }
  }
}

template <typename Data>
constexpr typename AATree<Data>::Node&
AATree<Data>::Node::operator=(const Node& other) {
  if (this != &other) {
    this->level() = other.level();
    for (auto i = 0u; i < other.CHILDS_NUM; i++) {
      if (other.childs()[i]) {
        this->childs()[i] = new Node(*other.childs()[i]);
      }
    }
    this->value() = other.value();
  }
  return *this;
}

template <typename Data>
constexpr AATree<Data>::Node::Node(Node&& other)
  : level_(std::move(other.level())),
    value_(std::move(other.value())) {
  for (auto i = 0u; i < this->CHILDS_NUM; i++) {
    this->childs()[i] = other.childs()[i];
    other.childs()[i] = nullptr;
  }
}

template <typename Data>
constexpr typename AATree<Data>::Node&
AATree<Data>::Node::operator=(Node&& other) {
  this->level() = std::move(other.level());
  for (auto i = 0u; i < this->CHILDS_NUM; i++) {
    this->childs()[i] = other.childs()[i];
    other.childs()[i] = nullptr;
  }
  this->value() = std::move(other.value());
  return *this;
}

template <typename Data>
constexpr const typename AATree<Data>::value_type&
AATree<Data>::Node::value() const {
  return this->value_;
}

template <typename Data>
constexpr typename AATree<Data>::value_type&
AATree<Data>::Node::value() {
  return this->value_;
}

template <typename Data>
constexpr const std::size_t& AATree<Data>::Node::level() const {
  return this->level_;
}

template <typename Data>
constexpr std::size_t& AATree<Data>::Node::level() { return this->level_; }

template <typename Data>
constexpr const typename AATree<Data>::Node::childs_type&
AATree<Data>::Node::childs() const {
  return this->childs_;
}

template <typename Data>
constexpr typename AATree<Data>::Node::childs_type&
AATree<Data>::Node::childs() {
  return this->childs_;
}

template <typename Data>
constexpr const typename AATree<Data>::Node*&
AATree<Data>::Node::left() const {
  return this->childs_[0];
}

template <typename Data>
constexpr typename AATree<Data>::Node*&
AATree<Data>::Node::left() {
  return this->childs_[0];
}

template <typename Data>
constexpr const typename AATree<Data>::Node*&
AATree<Data>::Node::right() const {
  return this->childs_[1];
}

template <typename Data>
constexpr typename AATree<Data>::Node*&
AATree<Data>::Node::right() {
  return this->childs_[1];
}

template <typename Data>
constexpr AATree<Data>::Node::~Node() {
  for (auto* child : this->childs()) {
    if (child) {
      delete child;
    }
  }
}

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
constexpr typename AATree<Data>::Node*&
AATree<Data>::skew(AATree<Data>::Node*& node) {
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
constexpr typename AATree<Data>::Node*&
AATree<Data>::split(AATree<Data>::Node*& node) {
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
constexpr typename AATree<Data>::Node*
AATree<Data>::successor(Node* node) {
  auto* ret = node->right();
  while (ret->left()) {
    ret = ret->left();
  }
  return ret;
}

template <typename Data>
constexpr typename AATree<Data>::Node*
AATree<Data>::predecessor(Node* node) {
  auto* ret = node->left();
  while (ret->right()) {
    ret = ret->right();
  }
  return ret;
}

template <typename Data>
constexpr typename AATree<Data>::Node*
AATree<Data>::decrease(Node* node) {
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
constexpr typename AATree<Data>::Node* const &
AATree<Data>::root() const {
  return this->root_;
}

template <typename Data>
constexpr typename AATree<Data>::Node*&
AATree<Data>::root() {
  return this->root_;
}

template <typename Data>
constexpr typename AATree<Data>::Node*
AATree<Data>::insert(
    const typename AATree<Data>::value_type& val,
    AATree<Data>::Node*& node
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
constexpr typename AATree<Data>::Node*
AATree<Data>::remove(
    const typename AATree<Data>::value_type& val,
    AATree<Data>::Node*& node
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
constexpr typename AATree<Data>::Node*
AATree<Data>::find(
    const typename AATree<Data>::value_type& val,
    AATree<Data>::Node* const & node
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
constexpr typename AATree<Data>::Node*
AATree<Data>::insert(const typename AATree<Data>::value_type& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::Node*
AATree<Data>::insert(typename AATree<Data>::value_type&& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::Node*
AATree<Data>::remove(const typename AATree<Data>::value_type& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::Node*
AATree<Data>::remove(typename AATree<Data>::value_type&& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::Node*
AATree<Data>::find(const typename AATree<Data>::value_type& val) const {
  return this->find(val, this->root());
}

template <typename Data>
constexpr typename AATree<Data>::Node*
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
