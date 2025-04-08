#include "tree.hpp"

int main() {
    SearchTree::AVLTree tree(9);
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(-2);
    tree.dump_gv();
}