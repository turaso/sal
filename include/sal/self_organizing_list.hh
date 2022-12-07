#ifndef SAL_SELF_ORGANIZING_LIST_HH_
#define SAL_SELF_ORGANIZING_LIST_HH_

#include <sal/double_linked_list.hh>

namespace sal {

template <typename Data>
class SelfOrganizingList : public DoubleLinkedList<Data> {
public:
  using value_type = Data;
  virtual ~SelfOrganizingList() = default;
protected:
  using DoubleLinkedList<Data>::find;
  constexpr typename DoubleLinkedList<Data>::template Node<value_type>*
      find(const value_type&);
private:
};

} /// namespace sal

namespace sal {

template <typename Data>
constexpr typename DoubleLinkedList<Data>::template
Node<typename SelfOrganizingList<Data>::value_type>*
SelfOrganizingList<Data>::find(
    const SelfOrganizingList<Data>::value_type& val
) {
  auto* it = util::as_mutable(std::as_const(*this).find(val));
  if (!it) {
    return nullptr;
  }
  if (it->prev()) {
    if (it->next()) {
      it->next()->prev() = it->prev();
    }
    it->prev()->next() = it->next();
    it->next() = it->prev();
    it->prev() = it->prev()->prev();
    if (!it->prev()) {
      this->root() = it;
    } else {
      it->prev()->next() = it;
    }
    it->next()->prev() = it;
    if (!it->next()->next()) {
      this->last() = it->next();
    }
  }
  return it;
}

} /// namespace sal

#endif /// SAL_SELF_ORGANIZING_LIST_HH_
