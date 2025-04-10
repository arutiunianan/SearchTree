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
    void addNode(int value, std::unique_ptr<Node>& node);

    void balance(std::unique_ptr<Node>& node);
    void balanceLeft(std::unique_ptr<Node>& node);
    void balanceRight(std::unique_ptr<Node>& node);
};

}  // namespace SearchTree