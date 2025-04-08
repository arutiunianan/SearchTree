#include "tree.hpp"

namespace SearchTree {

void AVLTree::balance(std::unique_ptr<Node> &node) {
    if(node->getLeftChild()->height_)
}

void AVLTree::rotate(std::unique_ptr<Node> &node1, std::unique_ptr<Node> &node2) {
    std::swap(node1->height_, node2->height_);
    std::swap(node1, node2);
}

size_t AVLTree::addNode(int value, std::unique_ptr<Node> &node) {
    size_t height = 0;
    if(node->value_ > value) {
        if(node->getLeftChild().get() == nullptr) {
            node->addLeftChild(value);
            height = 1;
        }
        else {
            height = addNode(value, node->getLeftChild());
        }
    }
    else {
        if(node->getRightChild().get() == nullptr) {
            node->addRightChild(value);
            height = 1;
        }
        else {
            height = addNode(value, node->getRightChild());
        }
    }

    ++node->desc_num_;
    node->height_ = std::max(height, node->height_);

    balance(node);

    return node->height_ + 1;
}

void AVLTree::dump_gv() const {
    std::cout << "digraph structs {\n";
    root->dump_gv();
    std::cout << "}";
}

} // namespace SearchTree