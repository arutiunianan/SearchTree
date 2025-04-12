#pragma once

#include "node.hpp"

#include <utility>

namespace SearchTree {

class AVLTree final {
   private:
    using node_type = int;
    std::unique_ptr<Node<node_type>> root;

   public:
    AVLTree() {}
    AVLTree(node_type root_value)
        : root(std::make_unique<Node<node_type>>(root_value)) {}

    void addNode(int value) {
        if (root.get() == nullptr) {
            root = std::make_unique<Node<node_type>>(value);
            return;
        }
        addNode(value, root);
    }

    size_t findDistance(node_type lower_key, node_type upper_key) const;

    void dump_gv() const;

   private:
    void addNode(node_type value, std::unique_ptr<Node<node_type>>& node);

    void balance(std::unique_ptr<Node<node_type>>& node);
    void balanceLeft(std::unique_ptr<Node<node_type>>& node);
    void balanceRight(std::unique_ptr<Node<node_type>>& node);

    size_t findNumOfLarge(node_type value,
                          const std::unique_ptr<Node<node_type>>& node) const;
    size_t findNumOfSmaller(node_type value,
                            const std::unique_ptr<Node<node_type>>& node) const;
    size_t findNumOfLarge(node_type value) const {
        return findNumOfLarge(value, root);
    }
    size_t findNumOfSmaller(node_type value) const {
        return findNumOfSmaller(value, root);
    }
};

}  // namespace SearchTree