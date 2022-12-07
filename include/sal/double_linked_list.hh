#ifndef SAL_DOUBLE_LINKED_LIST_HH_
#define SAL_DOUBLE_LINKED_LIST_HH_

#include <algorithm>
#include <utility>

#include <sal/util.hh>
#include <sal/node_base.hh>

namespace sal {

template <typename Data>
class DoubleLinkedList {
public:
  using value_type = Data;
  template <NodeValue T>
  class Node : public NodeBase<T> {
  public:
    constexpr Node(T val);
    constexpr Node* const & prev() const;
    constexpr Node*& prev();
    constexpr Node* const & next() const;
    constexpr Node*& next();
    virtual ~Node();
  protected:
    Node* prev_ = nullptr;
    Node* next_ = nullptr;
  private:
  };
  constexpr static Node<value_type>* nil = nullptr;
  constexpr Node<value_type>* const & root() const;
  constexpr Node<value_type>*& root();
  constexpr Node<value_type>* const & last() const;
  constexpr Node<value_type>*& last();
  virtual constexpr Node<value_type>* add(const value_type&);
  virtual constexpr Node<value_type>* add(value_type&&);
  virtual constexpr Node<value_type>* get(const value_type&);
  virtual constexpr Node<value_type>* get(value_type&&);
  virtual constexpr Node<value_type>* const & get(const value_type&) const;
  virtual constexpr Node<value_type>* const & get(value_type&&) const;
  virtual constexpr bool del(const value_type&);
  virtual constexpr bool del(value_type&&);
  virtual ~DoubleLinkedList();
protected:
  virtual constexpr Node<value_type>*& insert(const value_type&);
  virtual constexpr Node<value_type>* const & find(const value_type&) const;
  virtual constexpr bool remove(const value_type&);
  Node<value_type>* root_ = nullptr;
  Node<value_type>* last_ = nullptr;
private:
};

} /// namespace sal

namespace sal {

template <typename Data>
template <NodeValue T>
DoubleLinkedList<Data>::Node<T>::~Node() {
  if (this->next_) {
    delete this->next_;
  }
//  if (this->prev_) {
//    delete this->prev_;
//  }
}

template <typename Data>
template <NodeValue T>
constexpr DoubleLinkedList<Data>::Node<T>::Node(T value) : NodeBase<T>(value) {}

template <typename Data>
template <NodeValue T>
constexpr typename DoubleLinkedList<Data>::template Node<T>* const &
DoubleLinkedList<Data>::Node<T>::prev() const {
  return this->prev_;
}

template <typename Data>
template <NodeValue T>
constexpr typename DoubleLinkedList<Data>::template Node<T>*&
DoubleLinkedList<Data>::Node<T>::prev() {
  return this->prev_;
}

template <typename Data>
template <NodeValue T>
constexpr typename DoubleLinkedList<Data>::template Node<T>* const &
DoubleLinkedList<Data>::Node<T>::next() const {
  return this->next_;
}

template <typename Data>
template <NodeValue T>
constexpr typename DoubleLinkedList<Data>::template Node<T>*&
DoubleLinkedList<Data>::Node<T>::next() {
  return this->next_;
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>* const &
DoubleLinkedList<Data>::root() const {
  return this->root_;
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>*&
DoubleLinkedList<Data>::root() {
  return this->root_;
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>* const &
DoubleLinkedList<Data>::last() const {
  return this->last_;
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>*&
DoubleLinkedList<Data>::last() {
  return this->last_;
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>*
DoubleLinkedList<Data>::add(
    const DoubleLinkedList<Data>::value_type& val
) {
  return this->insert(val);
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>*
DoubleLinkedList<Data>::add(
    DoubleLinkedList<Data>::value_type&& val
) {
  return this->insert(val);
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>*
DoubleLinkedList<Data>::get(
    const DoubleLinkedList<Data>::value_type& val
) {
  return util::as_mutable(this->find(val));
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>*
DoubleLinkedList<Data>::get(
    DoubleLinkedList<Data>::value_type&& val
) {
  return util::as_mutable(this->find(val));
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>* const &
DoubleLinkedList<Data>::get(
    const DoubleLinkedList<Data>::value_type& val
) const {
  return this->find(val);
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>* const &
DoubleLinkedList<Data>::get(
    DoubleLinkedList<Data>::value_type&& val
) const {
  return this->find(val);
}

template <typename Data>
constexpr bool DoubleLinkedList<Data>::del(
    const DoubleLinkedList<Data>::value_type& val
) {
  return this->remove(val);
}

template <typename Data>
constexpr bool DoubleLinkedList<Data>::del(
    DoubleLinkedList<Data>::value_type&& val
) {
  return this->remove(val);
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>*&
DoubleLinkedList<Data>::insert(
    const DoubleLinkedList<Data>::value_type& val
) {
  if (!this->last()) {
    this->root() = new Node<value_type>(std::move(val));
    return this->last() = this->root();
  } else {
    Node<value_type>* inserted = new Node<value_type>(std::move(val));
    this->last()->next() = inserted;
    inserted->prev() = this->last();
    return this->last() = inserted;
  }
}

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename DoubleLinkedList<Data>::value_type>* const &
DoubleLinkedList<Data>::find(
    const DoubleLinkedList<Data>::value_type& val
) const {
  auto* it = this->root();
  while (it) {
    if (it->value() == val) {
      if (it->prev()) {
        return it->prev()->next();
      } else if (it->next()) {
        return it->next()->prev();
      } else {
        return this->root();
      }
    } else if (!it->next()) {
      return DoubleLinkedList::nil;
    } else {
      it = it->next();
    }
  }
  return DoubleLinkedList::nil;
}

template <typename Data>
constexpr bool DoubleLinkedList<Data>::remove(
    const DoubleLinkedList<Data>::value_type& val
) {
  auto it = std::as_const(*this).find(val);
  if (!it) {
    return false;
  }
  if (it->prev()) {
    it->prev()->next() = it->next();
  } else {
    this->root() = it->next();
  }
  if (it->next()) {
    it->next()->prev() = it->prev();
  } else {
    this->last() = it->prev();
  }
  return true;
}

template <typename Data>
DoubleLinkedList<Data>::~DoubleLinkedList() {
  if (this->root()) {
    delete this->root();
  }
}

} /// namespace sal

#endif /// SAL_DOUBLE_LINKED_LIST_HH_
