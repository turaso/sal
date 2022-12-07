#include <sal/self_organizing_list.hh>
#include <cassert>

int main() {
  using data = unsigned;
  sal::SelfOrganizingList<data> list;
  assert(list.add(0));
  assert(list.root());
  assert(list.root()->value() == 0);
  assert(list.add(1));
  assert(list.root()->next());
  assert(list.root()->next()->value() == 1);
  assert(list.root()->next()->prev() == list.root());
  assert(!list.root()->next()->next());
  assert(list.get(0));
  assert(list.get(1));
  assert(!list.get(2));
  assert(list.del(1));
  assert(!list.del(1));
  assert(list.add(3));
  assert(list.add(4));
  assert(list.add(5));
  assert(list.del(0));
  assert(list.get(3));
  assert(list.get(4));
  assert(list.get(5));
  assert(list.del(5));
  assert(list.del(3));
  assert(list.del(4));
  assert(list.add(0));
  assert(list.add(2));
  assert(list.add(1));
  assert(list.get(0));
  assert(list.get(1));
  assert(list.get(2));
  assert(list.root());
  assert(list.root()->value() == 0);
  assert(list.root()->next());
  assert(list.root()->next()->value() == 2);
  assert(list.root()->next()->next());
  assert(list.root()->next()->next()->value() == 1);

  return 0;
}
