#pragma once

#include <iostream>
#include <memory>

namespace SearchTree {

template <typename T>
class Node final {
   private:
    std::unique_ptr<Node<T>> left_;
    std::unique_ptr<Node<T>> right_;

    size_t desc_num_ = 0;
    size_t height_ = 0;

   public:
    T value_ = 0;

   public:
    Node(T value) : value_(value) {}

    bool operator==(const Node& node) const {
        if (desc_num_ != node.desc_num_ || height_ != node.height_ ||
            value_ != node.value_) {
            return false;
        }

        if ((!left_ && node.left_) || (left_ && !(node.left_)) ||
            (!right_ && node.right_) || (right_ && !(node.right_))) {
            return false;
        }

        if ((left_ && node.left_ && !(*left_ == *(node.left_))) ||
            (right_ && node.right_ && !(*right_ == *(node.right_)))) {
            return false;
        }

        return true;
    }
    //bool operator!=(AVLTree tree);

    void addLeftChild(std::unique_ptr<Node<T>>& node) {
        left_ = std::move(node);
    }
    void addRightChild(std::unique_ptr<Node<T>>& node) {
        right_ = std::move(node);
    }

    void addLeftChild(T value) { left_ = std::make_unique<Node<T>>(value); }
    void addRightChild(T value) { right_ = std::make_unique<Node<T>>(value); }

    std::unique_ptr<Node<T>>& getLeftChild() { return left_; }
    std::unique_ptr<Node<T>>& getRightChild() { return right_; }

    static void swap(Node<T>& a, Node<T>& b) noexcept {
        std::swap(a.left_, b.left_);
        std::swap(a.right_, b.right_);
        std::swap(a.desc_num_, b.desc_num_);
        std::swap(a.height_, b.height_);
        std::swap(a.value_, b.value_);
    }

    static size_t computeHeight(const std::unique_ptr<Node<T>>& node) noexcept {
        return node ? node->height_ + 1 : 0;
    }
    size_t determineHeight() noexcept {
        if (left_.get() == nullptr && right_.get() == nullptr) {
            height_ = 0;
            return height_;
        }

        size_t left_height = computeHeight(left_);
        size_t right_height = computeHeight(right_);
        height_ = std::max(left_height, right_height);
        return height_;
    }

    static size_t computeDescNum(
        const std::unique_ptr<Node<T>>& node) noexcept {
        return node ? node->desc_num_ + 1 : 0;
    }
    size_t determineDescNum() noexcept {
        size_t left_desc_num = computeDescNum(left_);
        size_t right_desc_num = computeDescNum(right_);

        desc_num_ = left_desc_num + right_desc_num;
        return desc_num_;
    }

    void updateParameters() noexcept {
        determineHeight();
        determineDescNum();
    }

    std::vector<T> getElements() const {
        std::vector<T> elements;
        if (left_) {
            std::vector<T> left_elements = left_->getElements();
            elements.insert(elements.end(), left_elements.begin(),
                            left_elements.end());
        }
        elements.push_back(value_);
        if (right_) {
            std::vector<T> right_elements = right_->getElements();
            elements.insert(elements.end(), right_elements.begin(),
                            right_elements.end());
        }
        return elements;
    }

    void dump(std::ostream& ostr = std::cout) const {
        if (left_.get() != nullptr) {
            left_->dump();
        }

        ostr << value_ << " ";

        if (right_.get() != nullptr) {
            right_->dump();
        }
    }

    void dump_gv(std::ostream& ostr = std::cout) const {
        ostr << "    node" << this << "[shape=Mrecord, label=\"{" << value_
             << " | desc_num = " << desc_num_ << ", height = " << height_
             << "}\", style=filled, fillcolor=\"#C5E384\"]\n";

        if (left_.get() != nullptr) {
            ostr << "    node" << this << "->node" << left_.get()
                 << " [color = \"#ff0000\"]\n";
            left_->dump_gv();
        }

        if (right_.get() != nullptr) {
            ostr << "    node" << this << "->node" << right_.get()
                 << " [color = \"#40ff00\"]\n";
            right_->dump_gv();
        }
    }
};

}  // namespace SearchTree