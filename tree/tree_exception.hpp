#pragma once

#include <stdexcept>

#include "tree.hpp"

namespace SearchTree {

struct AVLException : public std::exception {
    explicit AVLException(const char* msg) : message_(msg) {}
    const char* what() const noexcept override { return message_; }

   private:
    const char* message_;
};

struct EmptyTreeException : public AVLException {
    EmptyTreeException() : AVLException("\n Operation on empty AVL tree") {}
};

struct NodeNullException : public AVLException {
    NodeNullException()
        : AVLException("\n Internal error: encountered null node") {}
};

struct UnbalancedTreeException : public AVLException {
    UnbalancedTreeException() : AVLException("\n Balancing the tree failed") {}
};

}  // namespace SearchTree