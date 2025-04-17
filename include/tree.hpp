#pragma once

#include <utility>
#include <vector>

#include "node.hpp"
#include "tree_exception.hpp"

namespace SearchTree {

class AVLTree final {
   private:
    using node_type = int;
    std::unique_ptr<Node<node_type>> root;

   public:
    AVLTree() {}
    AVLTree(node_type root_value)
        : root(std::make_unique<Node<node_type>>(root_value)) {}

    bool operator==(const AVLTree& tree) const;
    //bool operator!=(AVLTree tree);

    size_t size() const;
    bool empty() const;
    void insert(const node_type& value);
    void erase(const node_type& value);
    bool contains(const node_type& value) const;
    bool balanced() const;

    size_t findDistance(const node_type& lower_key,
                        const node_type& upper_key) const;

    std::vector<node_type> getElements() const;
    void dump(std::ostream& ostr = std::cout) const;
    void dump_gv(std::ostream& ostr = std::cout) const;

   private:
    void insert(const node_type& value, std::unique_ptr<Node<node_type>>& node);
    void erase(const node_type& value, std::unique_ptr<Node<node_type>>& node);
    bool contains(const node_type& value,
                  const std::unique_ptr<Node<node_type>>& node) const;

    node_type min(std::unique_ptr<Node<node_type>>& node) const;
    node_type max(std::unique_ptr<Node<node_type>>& node) const;

    void balance(std::unique_ptr<Node<node_type>>& node);
    void balanceLeft(std::unique_ptr<Node<node_type>>& node);
    void balanceRight(std::unique_ptr<Node<node_type>>& node);
    bool balanced(const std::unique_ptr<Node<node_type>>& node) const;

    size_t findNumOfLarge(const node_type& value,
                          const std::unique_ptr<Node<node_type>>& node) const;
    size_t findNumOfSmaller(const node_type& value,
                            const std::unique_ptr<Node<node_type>>& node) const;
    size_t findNumOfLarge(const node_type& value) const {
        return findNumOfLarge(value, root);
    }
    size_t findNumOfSmaller(const node_type& value) const {
        return findNumOfSmaller(value, root);
    }
};

//std::ostream& operator<<(std::ostream& ostr, const AVLTree& tree);

}  // namespace SearchTree