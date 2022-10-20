#include <sal/aa_tree.hh>
#include <sal/rb_tree.hh>
#include <sal/tree.hh>
#include <cassert>

int main() {
  {
    using data_type = int;
    using Tree = sal::Tree<data_type, sal::AATree>;
    {
      Tree tree;
      assert(tree.empty());
      assert(tree.insert(0));
      assert(!tree.insert(0));
      assert(tree.size() == 1);
      assert(tree.insert(1));
      assert(tree.insert(-1));
      assert(tree.insert(2));
      assert(tree.insert(-2));
      assert(tree.insert(3));
      assert(tree.insert(-3));
      assert(tree.size() == 7);
      assert(tree.remove(0));
      assert(tree.size() == 6);
      assert(!tree.remove(0));
    }
    {
      Tree tree = {-3, -2, -1, 0, 1, 2, 3};
      assert(tree.size() == 7);
    }
    {
      Tree tree;
      assert(tree.empty());
      assert(!tree.remove(0));
      assert(!tree.remove(1));
      assert(!tree.find(-1));
      assert(tree.empty());
    }
    {
      Tree tree = {};
      assert(tree.empty());
      assert(tree.size() == 0);
    }
    {
      const Tree smaller = {1, 2, 3};
      const Tree bigger = {4, 5, 6, 7};
      const auto sum = smaller + bigger;
      assert(sum.size() == smaller.size() + bigger.size());
      for (const auto& val : smaller.bfs()) {
        assert(sum.find(val));
      }
      for (const auto& val : bigger.bfs()) {
        assert(sum.find(val));
      }
    }
    {
      const Tree orig = {1, 2};
      const Tree::data_type value = 3;
      auto copy = value;
      const auto fork = orig + std::move(copy);
      assert(fork.size() == orig.size() + 1);
      for (const auto& val : orig.bfs()) {
        assert(fork.find(val));
      }
      assert(fork.find(value));
    }
    {
      const Tree orig = {1, 2};
      const Tree::data_type value = 3;
      const auto fork = orig + value;
      assert(fork.size() == orig.size() + 1);
      for (const auto& val : orig.bfs()) {
        assert(fork.find(val));
      }
      assert(fork.find(value));
    }
    {
      const Tree orig = {1, 2};
      const Tree other = {3, 4, 5};
      Tree movable = other;
      const auto sum = orig + std::move(movable);
      assert(sum.size() == 5);
      for (const auto& val : orig.bfs()) {
        assert(sum.find(val));
      }
      for (const auto& val : other.bfs()) {
        assert(sum.find(val));
      }
    }
    {
      const Tree orig = {1, 2};
      const std::initializer_list<data_type> other = {3, 4, 5};
      std::initializer_list movable = other;
      const auto sum = orig + std::move(movable);
      assert(sum.size() == 5);
      for (const auto& val : orig.bfs()) {
        assert(sum.find(val));
      }
      for (const auto& val : other) {
        assert(sum.find(val));
      }
    }
  }
  {
    using data_type = unsigned;
    using Tree = sal::Tree<data_type, sal::RBTree>;
    {
      Tree tree;
      assert(tree.empty());
      assert(tree.insert(256));
      assert(tree.size() == 1);
      assert(tree.find(256));
      assert(tree.remove(256));
      assert(tree.empty());
    }
    {
      Tree tree;
      constexpr auto N = 1024u;
      for (auto i = 0u; i < N; i++) {
        assert(tree.insert(i));
      }
      assert(tree.size() == N);
    }
  }

  return 0;
}
