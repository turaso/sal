#ifndef SAL_RB_TREE_HH_
#define SAL_RB_TREE_HH_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>

#include <sal/node_tree_binary_base.hh>

namespace sal {

template <typename Data>
class RBTree {
public:
  using value_type = Data;
  struct Direction {
    enum Value : unsigned {
      LEFT = 0,
      RIGHT = 1,
    };
    constexpr Direction(Value);
    constexpr Direction inv() const;
    constexpr operator Value() const;
    Value value = LEFT;
  };
  template <NodeValue T>
  class Node : public NodeTreeBinaryBase<Node, T> {
  public:
    enum class Color : bool {
      BLACK,
      RED,
    };
    using parent_type = Node*;
    constexpr Node() = default;
    constexpr Node(value_type);
    constexpr Node(value_type, parent_type);
    constexpr Node(const Node&) = default;
    constexpr Node& operator=(const Node&) = default;
    constexpr Node(Node&&) = default;
    constexpr Node& operator=(Node&&) = default;
    constexpr const Color& color() const;
    constexpr Color& color();
    constexpr const parent_type& parent() const;
    constexpr parent_type& parent();
    constexpr virtual ~Node() = default;
  protected:
    Color color_ = Color::RED;
    parent_type parent_ = nullptr;
  private:
  };
  using node_type = Node<value_type>;
  constexpr RBTree() = default;
  constexpr RBTree(const RBTree&);
  constexpr RBTree& operator=(const RBTree&);
  constexpr RBTree(RBTree&&);
  constexpr RBTree& operator=(RBTree&&);
  constexpr Node<Data>* const & root() const;
  constexpr Node<Data>*& root();
  constexpr Node<Data>* insert(const value_type&);
  constexpr Node<Data>* insert(value_type&&);
  constexpr Node<Data>* remove(const value_type&);
  constexpr Node<Data>* remove(value_type&&);
  constexpr Node<Data>* find(const value_type&) const;
  constexpr Node<Data>* find(value_type&&) const;
  constexpr virtual ~RBTree();
protected:
  constexpr static Node<Data>* successor(Node<Data>*);
  constexpr static Node<Data>* predecessor(Node<Data>*);
  constexpr Node<Data>* insert(Node<Data>*, Node<Data>*&, Node<Data>*);
  constexpr Node<Data>* insert(const value_type&, Node<Data>*&);
  constexpr Node<Data>* remove(const value_type&, Node<Data>*&);
  constexpr Node<Data>* remove(Node<Data>*& n);
  constexpr Node<Data>* find(const value_type&, Node<Data>* const &) const;
  constexpr Node<Data>* rotate(Node<Data>*&, const Direction&);
  constexpr Node<Data>* fix(Node<Data>*&);
  Node<Data>* root_ = nullptr;
private:
};

} /// namespace sal

namespace sal {

template <typename Data>
constexpr RBTree<Data>::Direction::Direction(Direction::Value _value)
  : value(_value) {}

template <typename Data>
constexpr typename RBTree<Data>::Direction
RBTree<Data>::Direction::inv() const {
  if (*this == Direction::Value::LEFT) {
    return Direction::Value::RIGHT;
  } else {
    return Direction::Value::LEFT;
  }
}

template <typename Data>
constexpr RBTree<Data>::Direction::operator
RBTree<Data>::Direction::Value() const {
  return this->value;
}

template <typename Data>
template <NodeValue T>
constexpr RBTree<Data>::Node<T>::Node(
    RBTree<Data>::value_type value,
    RBTree<Data>::Node<T>::parent_type parent
) : NodeTreeBinaryBase<Node, T>(value), parent_(parent) {}

template <typename Data>
template <NodeValue T>
constexpr RBTree<Data>::Node<T>::Node(
    RBTree<Data>::value_type value
) : NodeTreeBinaryBase<Node, T>(value) {}

template <typename Data>
template <NodeValue T>
constexpr const typename RBTree<Data>::template Node<T>::Color&
RBTree<Data>::Node<T>::color() const { return this->color_; }

template <typename Data>
template <NodeValue T>
constexpr typename RBTree<Data>::template Node<T>::Color&
RBTree<Data>::Node<T>::color() { return this->color_; }

template <typename Data>
template <NodeValue T>
constexpr const typename RBTree<Data>::template Node<T>::parent_type&
RBTree<Data>::Node<T>::parent() const { return this->parent_; }

template <typename Data>
template <NodeValue T>
constexpr typename RBTree<Data>::template Node<T>::parent_type&
RBTree<Data>::Node<T>::parent() { return this->parent_; }

template <typename Data>
constexpr RBTree<Data>::RBTree(const RBTree& other) {
  if (other.root()) {
    this->root() = new Node(*other.root());
  }
}

template <typename Data>
constexpr RBTree<Data>& RBTree<Data>::operator=(const RBTree& other) {
  if (this != &other) {
    if (other.root()) {
      this->root() = new Node(*other.root());
    }
  }
  return *this;
}

template <typename Data>
constexpr RBTree<Data>::RBTree(RBTree&& other) {
  if (other.root()) {
    this->root() = new Node(std::move(*other.root()));
    other.root() = nullptr;
  }
}

template <typename Data>
constexpr RBTree<Data>& RBTree<Data>::operator=(RBTree&& other) {
  if (this != &other) {
    if (other.root()) {
      this->root() = new Node(std::move(*other.root()));
      other.root() = nullptr;
    }
  }
  return *this;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::successor(node_type* node) {
  auto* ret = node->right();
  while (ret->left()) {
    ret = ret->left();
  }
  return ret;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::predecessor(node_type* node) {
  auto* ret = node->left();
  while (ret->right()) {
    ret = ret->right();
  }
  return ret;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type* const &
RBTree<Data>::root() const {
  return this->root_;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*&
RBTree<Data>::root() {
  return this->root_;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::insert(
    RBTree<Data>::node_type* insertable,
    RBTree<Data>::node_type*& node,
    RBTree<Data>::node_type* parent
) {
  if (!node) {
    node = insertable;
    insertable->parent() = parent;
  } else if (insertable->value() <= node->value()) {
    node->left() = this->insert(insertable, node->left(), node);
  } else {
    node->right() = this->insert(insertable, node->right(), node);
  }
  return node;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::insert(
    const typename RBTree<Data>::value_type& val,
    RBTree<Data>::node_type*& node
) {
  auto* insertable = new node_type(val);
  this->insert(insertable, node, node ? node->parent() : nullptr);
  this->fix(insertable);
  this->root()->color() = node_type::Color::BLACK;
  return node;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::remove(
    const typename RBTree<Data>::value_type& val,
    RBTree<Data>::node_type*& node
) {
  if (!node) {
    return node;
  } else if (val > node->value()) {
    return this->remove(val, node->right());
  } else if (val < node->value()) {
    return this->remove(val, node->left());
  } else {
    return this->remove(node);
  }
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::find(
    const typename RBTree<Data>::value_type& val,
    RBTree<Data>::node_type* const & node
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
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::insert(const typename RBTree<Data>::value_type& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::insert(typename RBTree<Data>::value_type&& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::remove(const typename RBTree<Data>::value_type& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::remove(typename RBTree<Data>::value_type&& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::find(const typename RBTree<Data>::value_type& val) const {
  return this->find(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::find(typename RBTree<Data>::value_type&& val) const {
  return this->find(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::rotate(typename RBTree<Data>::node_type*& n, const Direction& dir) {
  typename RBTree<Data>::node_type* g = n->parent();
  typename RBTree<Data>::node_type* s =
      n->childs()[dir.inv()];
  typename RBTree<Data>::node_type* c;
  c = s->childs()[dir];
  n->childs()[dir.inv()] = c;
  if (c) {
    c->parent() = n;
  }
  s->childs()[dir] = n;
  n->parent() = s;
  s->parent() = g;
  if (g) {
    g->childs()[n == g->right() ? Direction::RIGHT : Direction::LEFT] = s;
  } else {
    this->root() = s;
  }
  return s;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::fix(typename RBTree<Data>::node_type*& n) {
  RBTree<Data>::node_type* p = n->parent(); /// parent
  if (!p) {
    this->root() = n;
    return n;
  }
  typename RBTree<Data>::node_type* g; /// grandparent
  typename RBTree<Data>::node_type* u; /// uncle
  typename RBTree<Data>::node_type* copy = n;
  do {
    if (p->color() == node_type::Color::BLACK) {
      return n;
    } else if (!(g = p->parent())) {
      p->color() = node_type::Color::BLACK;
      return n;
    }
    const Direction dir = (p == g->left()) ? Direction::LEFT : Direction::RIGHT;
    u = g->childs()[dir.inv()];
    if (!u || u->color() == node_type::Color::BLACK) {
      if (copy == (dir == Direction::LEFT ? p->right() : p->left())) {
        this->rotate(p, dir);
        copy = p;
        p = g->childs()[dir];
      }
      this->rotate(g, dir.inv());
      p->color() = node_type::Color::BLACK;
      g->color() = node_type::Color::RED;
      return n;
    }
    p->color() = node_type::Color::BLACK;
    u->color() = node_type::Color::BLACK;
    g->color() = node_type::Color::RED;
    copy = g;
  } while ((p = copy->parent()));
  return n;
}

template <typename Data>
constexpr typename RBTree<Data>::node_type*
RBTree<Data>::remove(typename RBTree<Data>::node_type*& n) {
  /// ?? static constexpr
  const std::function<void(typename RBTree<Data>::node_type*&)> case1 =
      [this, &case1](typename RBTree<Data>::node_type*& n) {
    const auto case2 =
        [this, &case1](typename RBTree<Data>::node_type*& n) {
      const Direction dir = (n == n->parent()->left()) ?
          Direction::LEFT :
          Direction::RIGHT;
      RBTree<Data>::node_type* s = n->parent()->childs()[dir.inv()];
      const auto case3 =
          [this, &s, &case1, &dir](typename RBTree<Data>::node_type*& n) {
        const auto case4 =
            [this, &s, &dir](typename RBTree<Data>::node_type*& n) {
          const auto case5 =
              [this, &s, &dir](typename RBTree<Data>::node_type*& n) {
            const auto case6 =
                [this, &s, &dir](typename RBTree<Data>::node_type*& n) {
              s->color() = n->parent()->color();
              n->parent()->color() = node_type::Color::BLACK;
              s->childs()[dir.inv()]->color() = node_type::Color::BLACK;
              this->rotate(n->parent(), dir);
            };
            if (s->color() == node_type::Color::BLACK) {
              if (
                  s->childs()[dir] &&
                  s->childs()[dir]->color() == node_type::Color::RED &&
                  s->childs()[dir.inv()]->color() == node_type::Color::BLACK
              ) {
                s->color() = node_type::Color::RED;
                s->childs()[dir]->color() = node_type::Color::BLACK;
                this->rotate(s, dir.inv());
                s = n->parent()->childs()[dir.inv()];
              }
            }
            case6(n);
          };
          if (
              n->parent()->color() == node_type::Color::RED &&
              s->color() == node_type::Color::BLACK &&
              (!s->left() || s->left()->color() == node_type::Color::BLACK) &&
              (!s->right() || s->right()->color() == node_type::Color::BLACK)
          ) {
            s->color() = node_type::Color::RED;
            n->parent()->color() = node_type::Color::BLACK;
          } else {
            case5(n);
          }
        };
        if (
            n->parent()->color() == node_type::Color::BLACK &&
            s->color() == node_type::Color::BLACK &&
            (!s->left() || s->left()->color() == node_type::Color::BLACK) &&
            (!s->right() || s->right()->color() == node_type::Color::BLACK)
        ) {
          s->color() = node_type::Color::RED;
          case1(n->parent());
        } else {
          case4(n);
        }
      };
      if (s->color() == node_type::Color::RED) {
        n->parent()->color() = node_type::Color::RED;
        s->color() = node_type::Color::BLACK;
        this->rotate(n->parent(), dir);
        s = n->parent()->childs()[dir.inv()];
      }
      case3(n);
    };
    if (n->parent()) {
      case2(n);
    }
  };
  const auto withOneChild = [&case1](
      typename RBTree<Data>::node_type*& n,
      Direction dir
  ) {
    const auto exchange = [&dir](
      typename RBTree<Data>::node_type*& n
    ) {
      auto* copy = n;
      n = n->childs()[dir];
      n->parent() = copy->parent();
      return copy;
    };
    auto old = exchange(n);
    if (old->color() == node_type::Color::BLACK) {
      if (old->childs()[dir]->color() == node_type::Color::RED) {
        old->childs()[dir]->color() = node_type::Color::BLACK;
      } else {
        case1(old->childs()[dir]);
      }
    }
    old->childs()[dir] = nullptr;
    delete(old);
  };
  if (!n->left() && !n->right()) {
    if (n->color() == node_type::Color::BLACK) {
      case1(n);
    }
    delete n;
    n = nullptr;

  } else if (!n->left()) {
    withOneChild(n, Direction::RIGHT);
  } else if (!n->right()) {
    withOneChild(n, Direction::LEFT);
  } else {
    auto* successor = this->successor(n);
    if (successor->parent() == n) {
      n->value() = successor->value();
      successor->parent()->right() = successor->right();
      successor->right() = nullptr;
      if (successor->color() == node_type::Color::BLACK) {
        case1(successor);
      }
      delete successor;
      successor = nullptr;
    } else {
      n->value() = successor->value();
      successor->parent()->left() = successor->right();
      successor->right() = nullptr;
      if (successor->color() == node_type::Color::BLACK) {
        case1(successor);
      }
      delete successor;
      successor = nullptr;
    }
  }
  return nullptr;
}

template <typename Data>
constexpr RBTree<Data>::~RBTree() {
  if (this->root()) {
    delete this->root();
  }
}

} /// namespace sal

#endif /// SAL_RB_TREE_HH_
