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

    void dump_gv() const;

   private:
    size_t addNode(int value, std::unique_ptr<Node>& node);

    void balance(std::unique_ptr<Node>& node);
    void rotate(std::unique_ptr<Node>& node1, std::unique_ptr<Node>& node2);
};

}  // namespace SearchTree