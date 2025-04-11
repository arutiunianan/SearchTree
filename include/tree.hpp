#pragma once

#include "node.hpp"

#include <utility>

namespace SearchTree {

class AVLTree {
   private:
    std::unique_ptr<Node> root;

   public:
    AVLTree() {}
    AVLTree(int root_value) : root(std::make_unique<Node>(root_value)) {}

    void addNode(int value) {
        if (root.get() == nullptr) {
            root = std::make_unique<Node>(value);
            return;
        }
        addNode(value, root);
    }

    size_t findDistance(int lower_key, int upper_key) const;

    void dump_gv() const;

   private:
    void addNode(int value, std::unique_ptr<Node>& node);

    void balance(std::unique_ptr<Node>& node);
    void balanceLeft(std::unique_ptr<Node>& node);
    void balanceRight(std::unique_ptr<Node>& node);

    size_t findNumOfLarge(int value, const std::unique_ptr<Node>& node) const;
    size_t findNumOfSmaller(int value, const std::unique_ptr<Node>& node) const;
    size_t findNumOfLarge(int value) const {
        return findNumOfLarge(value, root);
    }
    size_t findNumOfSmaller(int value) const {
        return findNumOfSmaller(value, root);
    }
};

}  // namespace SearchTree