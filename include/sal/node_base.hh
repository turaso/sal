#ifndef SAL_NODE_BASE_HH_
#define SAL_NODE_BASE_HH_

#include <concepts>

namespace sal {

template <typename T>
concept NodeValue = std::is_default_constructible_v<T>;

template <NodeValue T>
class NodeBase {
public:
  using value_type = T;
  constexpr NodeBase() = default;
  constexpr NodeBase(value_type);
  constexpr NodeBase(const NodeBase&) = default;
  constexpr NodeBase& operator=(const NodeBase&) = default;
  constexpr NodeBase(NodeBase&&) = default;
  constexpr NodeBase& operator=(NodeBase&&) = default;
  constexpr const value_type& value() const;
  constexpr value_type& value();
  constexpr virtual ~NodeBase() = default;
protected:
  value_type value_{};
private:
};

} /// namespace sal

namespace sal {

template <NodeValue T>
constexpr NodeBase<T>::NodeBase(typename NodeBase<T>::value_type value)
  : value_(value) {}

template <NodeValue T>
constexpr const typename NodeBase<T>::value_type&
NodeBase<T>::value() const {
  return this->value_;
}

template <NodeValue T>
constexpr typename NodeBase<T>::value_type&
NodeBase<T>::value() {
  return this->value_;
}

} /// namespace sal

#endif /// SAL_NODE_BASE_HH_
