#ifndef SAL_NODE_TREE_BINARY_BASE_HH_
#define SAL_NODE_TREE_BINARY_BASE_HH_

#include <sal/node_tree_base.hh>

namespace sal {

template <template <typename> class NodeType, NodeValue T>
class NodeTreeBinaryBase : public NodeTreeBase<NodeType, T, 2> {
public:
  using value_type = T;
  using node_type = NodeType<T>;
  constexpr NodeTreeBinaryBase() = default;
  constexpr NodeTreeBinaryBase(value_type);
  constexpr NodeTreeBinaryBase(const NodeTreeBinaryBase&) = default;
  constexpr NodeTreeBinaryBase& operator=(const NodeTreeBinaryBase&) = default;
  constexpr NodeTreeBinaryBase(NodeTreeBinaryBase&&) = default;
  constexpr NodeTreeBinaryBase& operator=(NodeTreeBinaryBase&&) = default;
  constexpr const NodeType<T>*& left() const;
  constexpr NodeType<T>*& left();
  constexpr const NodeType<T>*& right() const;
  constexpr NodeType<T>*& right();
  constexpr virtual ~NodeTreeBinaryBase() = default;
protected:
private:
};

} /// namespace sal

namespace sal {

template <template <typename> class NodeType, NodeValue T>
constexpr NodeTreeBinaryBase<NodeType, T>::NodeTreeBinaryBase(
    typename NodeTreeBinaryBase<NodeType, T>::value_type value
) : NodeTreeBase<NodeType, T, 2>(value) {}

template <template <typename> class NodeType, NodeValue T>
constexpr const typename NodeTreeBinaryBase<NodeType, T>::node_type*&
NodeTreeBinaryBase<NodeType, T>::left() const {
  return this->childs_[0];
}

template <template <typename> class NodeType, NodeValue T>
constexpr typename NodeTreeBinaryBase<NodeType, T>::node_type*&
NodeTreeBinaryBase<NodeType, T>::left() {
  return this->childs_[0];
}

template <template <typename> class NodeType, NodeValue T>
constexpr const typename NodeTreeBinaryBase<NodeType, T>::node_type*&
NodeTreeBinaryBase<NodeType, T>::right() const {
  return this->childs_[1];
}

template <template <typename> class NodeType, NodeValue T>
constexpr typename NodeTreeBinaryBase<NodeType, T>::node_type*&
NodeTreeBinaryBase<NodeType, T>::right() {
  return this->childs_[1];
}

} /// namesapce sal

#endif /// SAL_NODE_TREE_BINARY_BASE_HH_
