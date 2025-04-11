#include "tree.hpp"

namespace SearchTree {

size_t AVLTree::findDistance(int lower_key, int upper_key) const {
    if (root.get() == nullptr || lower_key > upper_key) {
        return 0;
    }

    size_t num_of_nodes = root->desc_num_ + 1;
    size_t num_of_large = findNumOfLarge(lower_key);
    size_t num_of_smaller = findNumOfSmaller(upper_key);
    return num_of_large + num_of_smaller - num_of_nodes;
}

size_t AVLTree::findNumOfLarge(int value,
                               const std::unique_ptr<Node>& node) const {
    size_t num_of_large = 0;

    if (node->value_ >= value) {
        if (node->getRightChild().get() != nullptr) {
            num_of_large += node->getRightChild()->desc_num_ + 1;
        }
        if (node->getLeftChild().get() != nullptr) {
            num_of_large += findNumOfLarge(value, node->getLeftChild());
        }
        ++num_of_large;
    } else {
        if (node->getRightChild().get() != nullptr) {
            num_of_large += findNumOfLarge(value, node->getRightChild());
        }
    }

    return num_of_large;
}

size_t AVLTree::findNumOfSmaller(int value,
                                 const std::unique_ptr<Node>& node) const {
    size_t num_of_smaller = 0;

    if (node->value_ <= value) {
        if (node->getLeftChild().get() != nullptr) {
            num_of_smaller += node->getLeftChild()->desc_num_ + 1;
        }
        if (node->getRightChild().get() != nullptr) {
            num_of_smaller += findNumOfSmaller(value, node->getRightChild());
        }
        ++num_of_smaller;
    } else {
        if (node->getLeftChild().get() != nullptr) {
            num_of_smaller += findNumOfSmaller(value, node->getLeftChild());
        }
    }

    return num_of_smaller;
}

void AVLTree::balance(std::unique_ptr<Node>& node) {
    size_t left_height = Node::computeChildHeight(node->getLeftChild());
    size_t right_height = Node::computeChildHeight(node->getRightChild());

    if (right_height >= left_height + 2) {
        balanceRight(node);
    } else if (left_height >= right_height + 2) {
        balanceLeft(node);
    }
}

void AVLTree::balanceRight(std::unique_ptr<Node>& node) {
    std::unique_ptr<Node> right_subtree = std::move(node->getRightChild());
    if (Node::computeChildHeight(right_subtree->getLeftChild()) <=
        Node::computeChildHeight(right_subtree->getRightChild())) {
        node->getRightChild() = std::move(right_subtree->getLeftChild());
        node->updateParameters();
        right_subtree->getLeftChild() = std::move(node);
        right_subtree->updateParameters();
        std::swap(right_subtree, node);
    } else {
        std::unique_ptr<Node> pivot_node =
            std::move(right_subtree->getLeftChild());
        node->getRightChild() = std::move(pivot_node->getLeftChild());
        node->updateParameters();
        right_subtree->getLeftChild() = std::move(pivot_node->getRightChild());
        right_subtree->updateParameters();
        pivot_node->getLeftChild() = std::move(node);
        pivot_node->getRightChild() = std::move(right_subtree);
        pivot_node->updateParameters();
        std::swap(pivot_node, node);
    }
}

void AVLTree::balanceLeft(std::unique_ptr<Node>& node) {
    std::unique_ptr<Node> left_subtree = std::move(node->getLeftChild());
    if (Node::computeChildHeight(left_subtree->getRightChild()) <=
        Node::computeChildHeight(left_subtree->getLeftChild())) {
        node->getLeftChild() = std::move(left_subtree->getRightChild());
        node->updateParameters();
        left_subtree->getRightChild() = std::move(node);
        left_subtree->updateParameters();
        std::swap(left_subtree, node);
    } else {
        std::unique_ptr<Node> pivot_node =
            std::move(left_subtree->getRightChild());
        node->getLeftChild() = std::move(pivot_node->getRightChild());
        node->updateParameters();
        left_subtree->getRightChild() = std::move(pivot_node->getLeftChild());
        left_subtree->updateParameters();
        pivot_node->getRightChild() = std::move(node);
        pivot_node->getLeftChild() = std::move(left_subtree);
        pivot_node->updateParameters();
        std::swap(pivot_node, node);
    }
}

void AVLTree::addNode(int value, std::unique_ptr<Node>& node) {
    if (node->value_ > value) {
        if (node->getLeftChild().get() == nullptr) {
            node->addLeftChild(value);
        } else {
            addNode(value, node->getLeftChild());
        }
    } else if (node->value_ < value) {
        if (node->getRightChild().get() == nullptr) {
            node->addRightChild(value);
        } else {
            addNode(value, node->getRightChild());
        }
    } else {
        return;
    }

    node->updateParameters();
    balance(node);
}

void AVLTree::dump_gv() const {
    std::cout << "digraph structs {\n";
    root->dump_gv();
    std::cout << "}";
}

}  // namespace SearchTree