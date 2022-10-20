#include <sal/sal.hxx>
#include <cassert>

int main() {
  using Tree = sal::RBTree<int>;
  constexpr auto BLACK = Tree::Node::Color::BLACK;
  constexpr auto RED = Tree::Node::Color::RED;
  {
    Tree tree;
    constexpr auto N = 8;
    for (auto i = 0; i < N; i++) {
      tree.insert(i);
      assert(tree.find(i));
      assert(!tree.find(i + 1));
    }
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 3);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == Tree::Node::Color::RED);
      assert(tree.root()->left()->value() == 1);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->left()->value() == 0);
      assert(!tree.root()->left()->left()->left());
      assert(!tree.root()->left()->left()->right());
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->right()->value() == 2);
      assert(!tree.root()->left()->right()->left());
      assert(!tree.root()->left()->right()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == Tree::Node::Color::RED);
      assert(tree.root()->right()->value() == 5);
      assert(tree.root()->right()->left());
      assert(tree.root()->right()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->left()->value() == 4);
      assert(!tree.root()->right()->left()->left());
      assert(!tree.root()->right()->left()->right());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->right()->value() == 6);
      assert(!tree.root()->right()->right()->left());
      assert(tree.root()->right()->right()->right());
      assert(tree.root()->right()->right()->right()->color() == Tree::Node::Color::RED);
      assert(tree.root()->right()->right()->right()->value() == 7);
      assert(!tree.root()->right()->right()->right()->left());
      assert(!tree.root()->right()->right()->right()->right());
    }
    tree.remove(7);
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 3);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == Tree::Node::Color::RED);
      assert(tree.root()->left()->value() == 1);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->left()->value() == 0);
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->right()->value() == 2);
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == Tree::Node::Color::RED);
      assert(tree.root()->right()->value() == 5);
      assert(tree.root()->right()->left());
      assert(tree.root()->right()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->left()->value() == 4);
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->right()->value() == 6);
      assert(!tree.root()->right()->right()->right());
    }
    tree.remove(6);
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 3);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == Tree::Node::Color::RED);
      assert(tree.root()->left()->value() == 1);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->left()->value() == 0);
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->right()->value() == 2);
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->value() == 5);
      assert(tree.root()->right()->left());
      assert(tree.root()->right()->left()->color() == Tree::Node::Color::RED);
      assert(tree.root()->right()->left()->value() == 4);
      assert(!tree.root()->right()->right());
    }
    tree.remove(5);
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 3);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == Tree::Node::Color::RED);
      assert(tree.root()->left()->value() == 1);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->left()->value() == 0);
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->right()->value() == 2);
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->value() == 4);
      assert(!tree.root()->right()->left());
      assert(!tree.root()->right()->right());
    }
    tree.remove(4);
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 1);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->value() == 0);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->value() == 3);
      assert(tree.root()->right()->left());
      assert(tree.root()->right()->left()->color() == Tree::Node::Color::RED);
      assert(tree.root()->right()->left()->value() == 2);
      assert(!tree.root()->right()->left()->left());
      assert(!tree.root()->right()->left()->right());
      assert(!tree.root()->right()->right());
    }
    tree.remove(3);
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 1);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->left()->value() == 0);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->right()->value() == 2);
      assert(!tree.root()->right()->left());
      assert(!tree.root()->right()->right());
    }
    tree.remove(2);
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 1);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == Tree::Node::Color::RED);
      assert(tree.root()->left()->value() == 0);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(!tree.root()->right());
    }
    tree.remove(1);
    {
      assert(tree.root());
      assert(tree.root()->color() == Tree::Node::Color::BLACK);
      assert(tree.root()->value() == 0);
      assert(!tree.root()->left());
      assert(!tree.root()->right());
    }
    tree.remove(0);
    {
      assert(!tree.root());
    }
  }
  {
    Tree tree;
    {
      assert(!tree.root());
      assert(!tree.find(0));
      assert(!tree.remove(0));
    }
    {
      tree.insert(256);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(!tree.root()->left());
      assert(!tree.root()->right());
    }
    {
      tree.insert(255);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == RED);
      assert(tree.root()->left()->value() == 255);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(!tree.root()->right());
    }
    {
      tree.insert(257);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == RED);
      assert(tree.root()->left()->value() == 255);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == RED);
      assert(tree.root()->right()->value() == 257);
      assert(!tree.root()->right()->left());
      assert(!tree.root()->right()->right());
    }
    {
      tree.insert(254);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == BLACK);
      assert(tree.root()->left()->value() == 255);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == RED);
      assert(tree.root()->left()->left()->value() == 254);
      assert(!tree.root()->left()->left()->left());
      assert(!tree.root()->left()->left()->right());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 257);
      assert(!tree.root()->right()->left());
      assert(!tree.root()->right()->right());
    }
    {
      tree.insert(258);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == BLACK);
      assert(tree.root()->left()->value() == 255);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == RED);
      assert(tree.root()->left()->left()->value() == 254);
      assert(!tree.root()->left()->left()->left());
      assert(!tree.root()->left()->left()->right());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 257);
      assert(!tree.root()->right()->left());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 258);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.insert(253);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == BLACK);
      assert(tree.root()->left()->value() == 254);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == RED);
      assert(tree.root()->left()->left()->value() == 253);
      assert(!tree.root()->left()->left()->left());
      assert(!tree.root()->left()->left()->right());
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == RED);
      assert(tree.root()->left()->right()->value() == 255);
      assert(!tree.root()->left()->right()->left());
      assert(!tree.root()->left()->right()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 257);
      assert(!tree.root()->right()->left());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 258);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.insert(259);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == BLACK);
      assert(tree.root()->left()->value() == 254);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == RED);
      assert(tree.root()->left()->left()->value() == 253);
      assert(!tree.root()->left()->left()->left());
      assert(!tree.root()->left()->left()->right());
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == RED);
      assert(tree.root()->left()->right()->value() == 255);
      assert(!tree.root()->left()->right()->left());
      assert(!tree.root()->left()->right()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 258);
      assert(tree.root()->right()->left());
      assert(tree.root()->right()->left()->color() == RED);
      assert(tree.root()->right()->left()->value() == 257);
      assert(!tree.root()->right()->left()->left());
      assert(!tree.root()->right()->left()->right());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 259);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.insert(252);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 256);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == RED);
      assert(tree.root()->left()->value() == 254);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == BLACK);
      assert(tree.root()->left()->left()->value() == 253);
      assert(tree.root()->left()->left()->left());
      assert(tree.root()->left()->left()->left()->color() == RED);
      assert(tree.root()->left()->left()->left()->value() = 252);
      assert(!tree.root()->left()->left()->left()->left());
      assert(!tree.root()->left()->left()->left()->right());
      assert(!tree.root()->left()->left()->right());
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == BLACK);
      assert(tree.root()->left()->right()->value() == 255);
      assert(!tree.root()->left()->right()->left());
      assert(!tree.root()->left()->right()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 258);
      assert(tree.root()->right()->left());
      assert(tree.root()->right()->left()->color() == RED);
      assert(tree.root()->right()->left()->value() == 257);
      assert(!tree.root()->right()->left()->left());
      assert(!tree.root()->right()->left()->right());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 259);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.remove(256);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 257);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == RED);
      assert(tree.root()->left()->value() == 254);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == BLACK);
      assert(tree.root()->left()->left()->value() == 253);
      assert(tree.root()->left()->left()->left());
      assert(tree.root()->left()->left()->left()->color() == RED);
      assert(tree.root()->left()->left()->left()->value() == 252);
      assert(!tree.root()->left()->left()->left()->left());
      assert(!tree.root()->left()->left()->left()->right());
      assert(!tree.root()->left()->left()->right());
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == BLACK);
      assert(tree.root()->left()->right()->value() == 255);
      assert(!tree.root()->left()->right()->left());
      assert(!tree.root()->left()->right()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 258);
      assert(!tree.root()->right()->left());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 259);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.remove(254);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 257);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == RED);
      assert(tree.root()->left()->value() == 253);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == BLACK);
      assert(tree.root()->left()->left()->value() == 252);
      assert(!tree.root()->left()->left()->left());
      assert(!tree.root()->left()->left()->right());
      assert(tree.root()->left()->right());
      assert(tree.root()->left()->right()->color() == BLACK);
      assert(tree.root()->left()->right()->value() == 255);
      assert(!tree.root()->left()->right()->left());
      assert(!tree.root()->left()->right()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 258);
      assert(!tree.root()->right()->left());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 259);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.remove(253);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 257);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == BLACK);
      assert(tree.root()->left()->value() == 255);
      assert(tree.root()->left()->left());
      assert(tree.root()->left()->left()->color() == RED);
      assert(tree.root()->left()->left()->value() == 252);
      assert(!tree.root()->left()->left()->left());
      assert(!tree.root()->left()->left()->right());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 258);
      assert(!tree.root()->right()->left());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 259);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.remove(255);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 257);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == BLACK);
      assert(tree.root()->left()->value() == 252);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 258);
      assert(!tree.root()->right()->left());
      assert(tree.root()->right()->right());
      assert(tree.root()->right()->right()->color() == RED);
      assert(tree.root()->right()->right()->value() == 259);
      assert(!tree.root()->right()->right()->left());
      assert(!tree.root()->right()->right()->right());
    }
    {
      tree.remove(252);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 258);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == BLACK);
      assert(tree.root()->left()->value() == 257);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(tree.root()->right());
      assert(tree.root()->right()->color() == BLACK);
      assert(tree.root()->right()->value() == 259);
      assert(!tree.root()->right()->left());
      assert(!tree.root()->right()->right());
    }
    {
      tree.remove(258);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 259);
      assert(tree.root()->left());
      assert(tree.root()->left()->color() == RED);
      assert(tree.root()->left()->value() == 257);
      assert(!tree.root()->left()->left());
      assert(!tree.root()->left()->right());
      assert(!tree.root()->right());
    }
    {
      tree.remove(259);
      assert(tree.root());
      assert(tree.root()->color() == BLACK);
      assert(tree.root()->value() == 257);
      assert(!tree.root()->left());
      assert(!tree.root()->right());
    }
    {
      tree.remove(257);
      assert(!tree.root());
    }
  }

  return 0;
}
