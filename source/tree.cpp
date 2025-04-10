#include "tree.hpp"

namespace SearchTree {

void AVLTree::balance(std::unique_ptr<Node>& node) {
    size_t left_hight = 0;
    size_t right_hight = 0;
    if (node->getLeftChild().get() != nullptr) {
        left_hight = node->getLeftChild()->height_ + 1;
    }
    if (node->getRightChild().get() != nullptr) {
        right_hight = node->getRightChild()->height_ + 1;
    }

    if (node->getRightChild().get() != nullptr &&
        right_hight >= 2 + left_hight) {
        auto tmp = std::move(node->getRightChild());
        if (tmp->getLeftChild().get() == nullptr ||
            (tmp->getRightChild() != nullptr &&
             tmp->getLeftChild()->height_ <= tmp->getRightChild()->height_)) {
            node->getRightChild() = std::move(tmp->getLeftChild());
            node->updateParameters();
            tmp->getLeftChild() = std::move(node);
            tmp->updateParameters();
            std::swap(tmp, node);
        } else if (tmp->getRightChild().get() == nullptr ||
                   (tmp->getLeftChild() != nullptr &&
                    tmp->getLeftChild()->height_ >
                        tmp->getRightChild()->height_)) {
            auto tmp1 = std::move(tmp->getLeftChild());
            node->getRightChild() = std::move(tmp1->getLeftChild());
            node->updateParameters();
            tmp->getLeftChild() = std::move(tmp1->getRightChild());
            tmp->updateParameters();
            tmp1->getLeftChild() = std::move(node);
            tmp1->getRightChild() = std::move(tmp);
            tmp1->updateParameters();
            std::swap(tmp1, node);
        }
    } else if (node->getLeftChild().get() != nullptr &&
               left_hight >= 2 + right_hight) {
        auto tmp = std::move(node->getLeftChild());
        if (tmp->getRightChild().get() == nullptr ||
            (tmp->getLeftChild() != nullptr &&
             tmp->getRightChild()->height_ <= tmp->getLeftChild()->height_)) {
            node->getLeftChild() = std::move(tmp->getRightChild());
            node->updateParameters();
            tmp->getRightChild() = std::move(node);
            tmp->updateParameters();
            std::swap(tmp, node);
        } else if (tmp->getLeftChild().get() == nullptr ||
                   (tmp->getRightChild() != nullptr &&
                    tmp->getRightChild()->height_ >
                        tmp->getLeftChild()->height_)) {
            auto tmp1 = std::move(tmp->getRightChild());
            node->getLeftChild() = std::move(tmp1->getRightChild());
            node->updateParameters();
            tmp->getRightChild() = std::move(tmp1->getLeftChild());
            tmp->updateParameters();
            tmp1->getRightChild() = std::move(node);
            tmp1->getLeftChild() = std::move(tmp);
            tmp1->updateParameters();
            std::swap(tmp1, node);
        }
    }
}

void AVLTree::rotate(std::unique_ptr<Node>& node1,
                     std::unique_ptr<Node>& node2) {
    std::swap(node1->height_, node2->height_);
    std::swap(node1, node2);
}

size_t AVLTree::addNode(int value, std::unique_ptr<Node>& node) {
    size_t height = 0;
    if (node->value_ > value) {
        if (node->getLeftChild().get() == nullptr) {
            node->addLeftChild(value);
            height = 1;
        } else {
            height = addNode(value, node->getLeftChild());
        }
    } else {
        if (node->getRightChild().get() == nullptr) {
            node->addRightChild(value);
            height = 1;
        } else {
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

}  // namespace SearchTree