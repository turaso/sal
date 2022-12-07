#ifndef SAL_NODE_TREE_BASE_HH_
#define SAL_NODE_TREE_BASE_HH_

#include <algorithm>
#include <utility>

#include <sal/node_base.hh>

namespace sal {

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
class NodeTreeBase : public NodeBase<T> {
public:
  using value_type = T;
  using node_type = NodeType<T>;
  static constexpr std::size_t CHILDS_NUM = CHILDS;
  template <typename Value>
  using container_type = Value[CHILDS_NUM];
  using childs_type = container_type<node_type*>;
  constexpr NodeTreeBase() = default;
  constexpr NodeTreeBase(value_type);
  constexpr NodeTreeBase(const NodeTreeBase&);
  constexpr NodeTreeBase& operator=(const NodeTreeBase&);
  constexpr NodeTreeBase(NodeTreeBase&&);
  constexpr NodeTreeBase& operator=(NodeTreeBase&&);
  constexpr const childs_type& childs() const;
  constexpr childs_type& childs();
  constexpr virtual ~NodeTreeBase();
protected:
  childs_type childs_{nullptr};
private:
};

} /// namespace sal

namespace sal {

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr NodeTreeBase<NodeType, T, CHILDS>::NodeTreeBase(
    typename NodeTreeBase<NodeType, T, CHILDS>::value_type value
) : NodeBase<T>(value) {}

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr NodeTreeBase<NodeType, T, CHILDS>::NodeTreeBase(
    const NodeTreeBase<NodeType, T, CHILDS>& other
) : NodeBase<T>(other), childs_(nullptr) {
  for (auto i = 0u; i < other.CHILDS_NUM; i++) {
    if (other.childs()[i]) {
      this->childs()[i] = new node_type(*other.childs()[i]);
    }
  }
}

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr NodeTreeBase<NodeType, T, CHILDS>&
NodeTreeBase<NodeType, T, CHILDS>::operator=(
    const NodeTreeBase<NodeType, T, CHILDS>& other
) {
  if (this != &other) {
    NodeBase<T>::operator=(other);
    this->color() = other.color();
    this->parent() = other.parent();
    for (auto i = 0u; i < other.CHILDS_NUM; i++) {
      if (other.childs()[i]) {
        this->childs()[i] = new node_type(*other.childs()[i]);
      }
    }
    this->value() = other.value();
  }
  return *this;
}

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr NodeTreeBase<NodeType, T, CHILDS>::NodeTreeBase(
    NodeTreeBase<NodeType, T, CHILDS>&& other
) : NodeBase<T>(other), childs_(nullptr) {
  for (auto i = 0u; i < this->CHILDS_NUM; i++) {
    this->childs()[i] = other.childs()[i];
    other.childs()[i] = nullptr;
  }
}

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr NodeTreeBase<NodeType, T, CHILDS>&
NodeTreeBase<NodeType, T, CHILDS>::operator=(
    NodeTreeBase<NodeType, T, CHILDS>&& other
) {
  NodeBase<T>::operator=(other);
  for (auto i = 0u; i < this->CHILDS_NUM; i++) {
    this->childs()[i] = other.childs()[i];
    other.childs()[i] = nullptr;
  }
  this->value() = std::move(other.value());
  return *this;
}

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr const typename NodeTreeBase<NodeType, T, CHILDS>::childs_type&
NodeTreeBase<NodeType, T, CHILDS>::childs() const {
  return this->childs_;
}

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr typename NodeTreeBase<NodeType, T, CHILDS>::childs_type&
NodeTreeBase<NodeType, T, CHILDS>::childs() {
  return this->childs_;
}

template <template<typename> class NodeType, NodeValue T, std::size_t CHILDS>
constexpr NodeTreeBase<NodeType, T, CHILDS>::~NodeTreeBase() {
  for (auto* child : this->childs()) {
    if (child) {
      delete child;
    }
  }
}

} /// namespace sal

#endif /// SAL_NODE_TREE_BASE_HH_
