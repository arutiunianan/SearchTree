#include "tree.hpp"

int main() {
    SearchTree::AVLTree tree{};
    tree.addNode(20);
    tree.addNode(10);
    tree.addNode(30);
    tree.addNode(80);
    tree.addNode(40);
    tree.addNode(60);
    tree.addNode(50);
    tree.addNode(70);
    tree.dump_gv();
}