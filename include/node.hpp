#pragma once

#include <iostream>
#include <memory>

namespace SearchTree {

class Node {
private:
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;

public:
    size_t desc_num_ = 0;
    size_t height_   = 0;
    int value_       = 0;

public:
    Node(int value): 
        value_(value) {}

    void addLeftChild(std::unique_ptr<Node> &node) {
        left_ = std::move(node);
    }
    void addRightChild(std::unique_ptr<Node> &node) {
        right_ = std::move(node);
    }

    void addLeftChild(int value) {
        left_ = std::make_unique<Node>(value);
    }
    void addRightChild(int value) {
        right_ = std::make_unique<Node>(value);
    }

    std::unique_ptr<Node> &getLeftChild() {
        return left_;
    }
    std::unique_ptr<Node> &getRightChild() {
        return right_;
    }

    void dump_gv() const {
        std::cout << "    node" << this << "[shape=Mrecord, label=\"{" 
                  << value_ << " | desc_num = " << desc_num_ << ", height = " << height_
                  << "}\", style=filled, fillcolor=\"#C5E384\"]\n";

        if(left_.get() != nullptr) {
            std::cout << "    node" << this << "->node" << left_.get()
                      << " [color = \"#293133\"]\n";
            left_->dump_gv();
        }

        if(right_.get() != nullptr) {
            std::cout << "    node" << this << "->node" << right_.get()
                      << " [color = \"#293133\"]\n";
            right_->dump_gv();
        }
    }
};

} // namespace SearchTree