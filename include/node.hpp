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
    size_t height_ = 0;
    int value_ = 0;

   public:
    Node(int value) : value_(value) {}

    void addLeftChild(std::unique_ptr<Node>& node) { left_ = std::move(node); }
    void addRightChild(std::unique_ptr<Node>& node) {
        right_ = std::move(node);
    }

    void addLeftChild(int value) { left_ = std::make_unique<Node>(value); }
    void addRightChild(int value) { right_ = std::make_unique<Node>(value); }

    std::unique_ptr<Node>& getLeftChild() { return left_; }
    std::unique_ptr<Node>& getRightChild() { return right_; }

    static void swap(Node& a, Node& b) noexcept {
        std::swap(a.left_, b.left_);
        std::swap(a.right_, b.right_);
        std::swap(a.desc_num_, b.desc_num_);
        std::swap(a.height_, b.height_);
        std::swap(a.value_, b.value_);
    }

    size_t determineHeight() {
        if (left_.get() == nullptr && right_.get() == nullptr) {
            height_ = 0;
            return height_;
        }

        size_t left_height = 0;
        size_t right_height = 0;

        if (left_.get() != nullptr) {
            left_height = left_->height_;
        }
        if (right_.get() != nullptr) {
            right_height = right_->height_;
        }

        height_ = std::max(left_height, right_height) + 1;
        return height_;
    }

    size_t determineDescNum() {
        size_t left_desc_num = 0;
        size_t right_desc_num = 0;

        if (left_.get() != nullptr) {
            left_desc_num = left_->desc_num_ + 1;
        }
        if (right_.get() != nullptr) {
            right_desc_num = right_->desc_num_ + 1;
        }
        desc_num_ = left_desc_num + right_desc_num;
        return desc_num_;
    }

    void updateParameters() {
        determineHeight();
        determineDescNum();
    }

    void dump_gv() const {
        std::cout << "    node" << this << "[shape=Mrecord, label=\"{" << value_
                  << " | desc_num = " << desc_num_ << ", height = " << height_
                  << "}\", style=filled, fillcolor=\"#C5E384\"]\n";

        if (left_.get() != nullptr) {
            std::cout << "    node" << this << "->node" << left_.get()
                      << " [color = \"#ff0000\"]\n";
            left_->dump_gv();
        }

        if (right_.get() != nullptr) {
            std::cout << "    node" << this << "->node" << right_.get()
                      << " [color = \"#40ff00\"]\n";
            right_->dump_gv();
        }
    }
};

}  // namespace SearchTree