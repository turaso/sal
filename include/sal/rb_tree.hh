#ifndef SAL_RB_TREE_HH_
#define SAL_RB_TREE_HH_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>

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
  class Node {
  public:
    enum class Color : bool {
      BLACK,
      RED,
    };
    static constexpr std::size_t CHILDS_NUM = 2;
    template <typename T>
    using container_type = T[CHILDS_NUM];
    using childs_type = container_type<Node*>;
    using parent_type = Node*;
    constexpr Node() = default;
    constexpr Node(value_type);
    constexpr Node(value_type, parent_type);
    constexpr Node(const Node&);
    constexpr Node& operator=(const Node&);
    constexpr Node(Node&&);
    constexpr Node& operator=(Node&&);
    constexpr const value_type& value() const;
    constexpr value_type& value();
    constexpr const Color& color() const;
    constexpr Color& color();
    constexpr const parent_type& parent() const;
    constexpr parent_type& parent();
    constexpr const childs_type& childs() const;
    constexpr childs_type& childs();
    constexpr const Node*& left() const;
    constexpr Node*& left();
    constexpr const Node*& right() const;
    constexpr Node*& right();
    constexpr virtual ~Node();
  protected:
    Color color_ = Color::RED;
    parent_type parent_ = nullptr;
    childs_type childs_{nullptr};
    value_type value_{};
  private:
  };
  constexpr RBTree() = default;
  constexpr RBTree(const RBTree&);
  constexpr RBTree& operator=(const RBTree&);
  constexpr RBTree(RBTree&&);
  constexpr RBTree& operator=(RBTree&&);
  constexpr Node* const & root() const;
  constexpr Node*& root();
  constexpr Node* insert(const value_type&);
  constexpr Node* insert(value_type&&);
  constexpr Node* remove(const value_type&);
  constexpr Node* remove(value_type&&);
  constexpr Node* find(const value_type&) const;
  constexpr Node* find(value_type&&) const;
  constexpr virtual ~RBTree();
protected:
  constexpr static Node* successor(Node*);
  constexpr static Node* predecessor(Node*);
  constexpr Node* insert(Node*, Node*&, Node*);
  constexpr Node* insert(const value_type&, Node*&);
  constexpr Node* remove(const value_type&, Node*&);
  constexpr Node* remove(Node*& n);
  constexpr Node* find(const value_type&, Node* const &) const;
  constexpr Node* rotate(Node*&, const Direction&);
  constexpr Node* fix(Node*&);
  Node* root_ = nullptr;
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
constexpr RBTree<Data>::Node::Node(
    RBTree<Data>::value_type value,
    RBTree<Data>::Node::parent_type parent
) : parent_(parent), value_(value) {}

template <typename Data>
constexpr RBTree<Data>::Node::Node(
    RBTree<Data>::value_type value
) : value_(value) {}

template <typename Data>
constexpr RBTree<Data>::Node::Node(const Node& other)
  : color_(other.color()),
    parent_(other.parent()),
    childs_(nullptr),
    value_(other.value()) {
  for (auto i = 0u; i < other.CHILDS_NUM; i++) {
    if (other.childs()[i]) {
      this->childs()[i] = new Node(*other.childs()[i]);
    }
  }
}

template <typename Data>
constexpr typename RBTree<Data>::Node&
RBTree<Data>::Node::operator=(const Node& other) {
  if (this != &other) {
    this->color() = other.color();
    this->parent() = other.parent();
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
constexpr RBTree<Data>::Node::Node(Node&& other)
  : color_(std::move(other.color())),
    parent_(std::move(other.parent())),
    value_(std::move(other.value())) {
  for (auto i = 0u; i < this->CHILDS_NUM; i++) {
    this->childs()[i] = other.childs()[i];
    other.childs()[i] = nullptr;
  }
}

template <typename Data>
constexpr typename RBTree<Data>::Node&
RBTree<Data>::Node::operator=(Node&& other) {
  this->color() = std::move(other.color());
  this->parent() = std::move(other.parent());
  for (auto i = 0u; i < this->CHILDS_NUM; i++) {
    this->childs()[i] = other.childs()[i];
    other.childs()[i] = nullptr;
  }
  this->value() = std::move(other.value());
  return *this;
}

template <typename Data>
constexpr const typename RBTree<Data>::value_type&
RBTree<Data>::Node::value() const {
  return this->value_;
}

template <typename Data>
constexpr typename RBTree<Data>::value_type&
RBTree<Data>::Node::value() {
  return this->value_;
}

template <typename Data>
constexpr const typename RBTree<Data>::Node::Color&
RBTree<Data>::Node::color() const { return this->color_; }

template <typename Data>
constexpr typename RBTree<Data>::Node::Color&
RBTree<Data>::Node::color() { return this->color_; }

template <typename Data>
constexpr const typename RBTree<Data>::Node::parent_type&
RBTree<Data>::Node::parent() const { return this->parent_; }

template <typename Data>
constexpr typename RBTree<Data>::Node::parent_type&
RBTree<Data>::Node::parent() { return this->parent_; }

template <typename Data>
constexpr const typename RBTree<Data>::Node::childs_type&
RBTree<Data>::Node::childs() const {
  return this->childs_;
}

template <typename Data>
constexpr typename RBTree<Data>::Node::childs_type&
RBTree<Data>::Node::childs() {
  return this->childs_;
}

template <typename Data>
constexpr const typename RBTree<Data>::Node*&
RBTree<Data>::Node::left() const {
  return this->childs_[0];
}

template <typename Data>
constexpr typename RBTree<Data>::Node*&
RBTree<Data>::Node::left() {
  return this->childs_[0];
}

template <typename Data>
constexpr const typename RBTree<Data>::Node*&
RBTree<Data>::Node::right() const {
  return this->childs_[1];
}

template <typename Data>
constexpr typename RBTree<Data>::Node*&
RBTree<Data>::Node::right() {
  return this->childs_[1];
}

template <typename Data>
constexpr RBTree<Data>::Node::~Node() {
  for (auto* child : this->childs()) {
    if (child) {
      delete child;
    }
  }
}

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
constexpr typename RBTree<Data>::Node*
RBTree<Data>::successor(Node* node) {
  auto* ret = node->right();
  while (ret->left()) {
    ret = ret->left();
  }
  return ret;
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::predecessor(Node* node) {
  auto* ret = node->left();
  while (ret->right()) {
    ret = ret->right();
  }
  return ret;
}

template <typename Data>
constexpr typename RBTree<Data>::Node* const &
RBTree<Data>::root() const {
  return this->root_;
}

template <typename Data>
constexpr typename RBTree<Data>::Node*&
RBTree<Data>::root() {
  return this->root_;
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::insert(
    RBTree<Data>::Node* insertable,
    RBTree<Data>::Node*& node,
    RBTree<Data>::Node* parent
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
constexpr typename RBTree<Data>::Node*
RBTree<Data>::insert(
    const typename RBTree<Data>::value_type& val,
    RBTree<Data>::Node*& node
) {
  auto* insertable = new Node(val);
  this->insert(insertable, node, node ? node->parent() : nullptr);
  this->fix(insertable);
  this->root()->color() = Node::Color::BLACK;
  return node;
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::remove(
    const typename RBTree<Data>::value_type& val,
    RBTree<Data>::Node*& node
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
constexpr typename RBTree<Data>::Node*
RBTree<Data>::find(
    const typename RBTree<Data>::value_type& val,
    RBTree<Data>::Node* const & node
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
constexpr typename RBTree<Data>::Node*
RBTree<Data>::insert(const typename RBTree<Data>::value_type& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::insert(typename RBTree<Data>::value_type&& val) {
  return this->insert(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::remove(const typename RBTree<Data>::value_type& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::remove(typename RBTree<Data>::value_type&& val) {
  return this->remove(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::find(const typename RBTree<Data>::value_type& val) const {
  return this->find(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::find(typename RBTree<Data>::value_type&& val) const {
  return this->find(val, this->root());
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::rotate(typename RBTree<Data>::Node*& n, const Direction& dir) {
  typename RBTree<Data>::Node* g = n->parent();
  typename RBTree<Data>::Node* s =
      n->childs()[dir.inv()];
  typename RBTree<Data>::Node* c;
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
constexpr typename RBTree<Data>::Node*
RBTree<Data>::fix(typename RBTree<Data>::Node*& n) {
  RBTree<Data>::Node* p = n->parent(); /// parent
  if (!p) {
    this->root() = n;
    return n;
  }
  typename RBTree<Data>::Node* g; /// grandparent
  typename RBTree<Data>::Node* u; /// uncle
  typename RBTree<Data>::Node* copy = n;
  do {
    if (p->color() == Node::Color::BLACK) {
      return n;
    } else if (!(g = p->parent())) {
      p->color() = Node::Color::BLACK;
      return n;
    }
    const Direction dir = (p == g->left()) ? Direction::LEFT : Direction::RIGHT;
    u = g->childs()[dir.inv()];
    if (!u || u->color() == Node::Color::BLACK) {
      if (copy == (dir == Direction::LEFT ? p->right() : p->left())) {
        this->rotate(p, dir);
        copy = p;
        p = g->childs()[dir];
      }
      this->rotate(g, dir.inv());
      p->color() = Node::Color::BLACK;
      g->color() = Node::Color::RED;
      return n;
    }
    p->color() = Node::Color::BLACK;
    u->color() = Node::Color::BLACK;
    g->color() = Node::Color::RED;
    copy = g;
  } while ((p = copy->parent()));
  return n;
}

template <typename Data>
constexpr typename RBTree<Data>::Node*
RBTree<Data>::remove(typename RBTree<Data>::Node*& n) {
  /// ?? static constexpr
  const std::function<void(typename RBTree<Data>::Node*&)> case1 =
      [this, &case1](typename RBTree<Data>::Node*& n) {
    const auto case2 =
        [this, &case1](typename RBTree<Data>::Node*& n) {
      const Direction dir = (n == n->parent()->left()) ?
          Direction::LEFT :
          Direction::RIGHT;
      RBTree<Data>::Node* s = n->parent()->childs()[dir.inv()];
      const auto case3 =
          [this, &s, &case1, &dir](typename RBTree<Data>::Node*& n) {
        const auto case4 =
            [this, &s, &dir](typename RBTree<Data>::Node*& n) {
          const auto case5 =
              [this, &s, &dir](typename RBTree<Data>::Node*& n) {
            const auto case6 =
                [this, &s, &dir](typename RBTree<Data>::Node*& n) {
              s->color() = n->parent()->color();
              n->parent()->color() = Node::Color::BLACK;
              s->childs()[dir.inv()]->color() = Node::Color::BLACK;
              this->rotate(n->parent(), dir);
            };
            if (s->color() == Node::Color::BLACK) {
              if (
                  s->childs()[dir] &&
                  s->childs()[dir]->color() == Node::Color::RED &&
                  s->childs()[dir.inv()]->color() == Node::Color::BLACK
              ) {
                s->color() = Node::Color::RED;
                s->childs()[dir]->color() = Node::Color::BLACK;
                this->rotate(s, dir.inv());
                s = n->parent()->childs()[dir.inv()];
              }
            }
            case6(n);
          };
          if (
              n->parent()->color() == Node::Color::RED &&
              s->color() == Node::Color::BLACK &&
              (!s->left() || s->left()->color() == Node::Color::BLACK) &&
              (!s->right() || s->right()->color() == Node::Color::BLACK)
          ) {
            s->color() = Node::Color::RED;
            n->parent()->color() = Node::Color::BLACK;
          } else {
            case5(n);
          }
        };
        if (
            n->parent()->color() == Node::Color::BLACK &&
            s->color() == Node::Color::BLACK &&
            (!s->left() || s->left()->color() == Node::Color::BLACK) &&
            (!s->right() || s->right()->color() == Node::Color::BLACK)
        ) {
          s->color() = Node::Color::RED;
          case1(n->parent());
        } else {
          case4(n);
        }
      };
      if (s->color() == Node::Color::RED) {
        n->parent()->color() = Node::Color::RED;
        s->color() = Node::Color::BLACK;
        this->rotate(n->parent(), dir);
        s = n->parent()->childs()[dir.inv()];
      }
      case3(n);
    };
    if (n->parent()) {
      case2(n);
    }
  };
  const auto withOneChild = [&case1](typename RBTree<Data>::Node*& n, Direction dir) {
    const auto exchange = [&dir](
      typename RBTree<Data>::Node*& n
    ) {
      auto* copy = n;
      n = n->childs()[dir];
      n->parent() = copy->parent();
      return copy;
    };
    auto old = exchange(n);
    if (old->color() == Node::Color::BLACK) {
      if (old->childs()[dir]->color() == Node::Color::RED) {
        old->childs()[dir]->color() = Node::Color::BLACK;
      } else {
        case1(old->childs()[dir]);
      }
    }
    old->childs()[dir] = nullptr;
    delete(old);
  };
  if (!n->left() && !n->right()) {
    if (n->color() == Node::Color::BLACK) {
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
      if (successor->color() == Node::Color::BLACK) {
        case1(successor);
      }
      delete successor;
      successor = nullptr;
    } else {
      n->value() = successor->value();
      successor->parent()->left() = successor->right();
      successor->right() = nullptr;
      if (successor->color() == Node::Color::BLACK) {
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
