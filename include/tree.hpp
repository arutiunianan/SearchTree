#pragma once

#include <iterator>
#include <stack>
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
    AVLTree() = default;
    explicit AVLTree(node_type root_value)
        : root(std::make_unique<Node<node_type>>(root_value)) {}

    template <bool is_const>
    class basic_iterator {
       private:
        using node_ptr_type =
            std::conditional_t<is_const, const Node<node_type>*,
                               Node<node_type>*>;
        std::stack<node_ptr_type> stack_;

        void push_left(node_ptr_type node) {
            while (node) {
                stack_.push(node);
                node = node->getLeftChild().get();
            }
        }

       public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Node<node_type>;
        using difference_type = std::ptrdiff_t;
        using pointer = node_ptr_type;
        using reference = std::conditional_t<is_const, const Node<node_type>&,
                                             Node<node_type>&>;

        basic_iterator() = default;
        explicit basic_iterator(node_ptr_type root) { push_left(root); }

        reference operator*() const { return *stack_.top(); }
        pointer operator->() const { return stack_.top(); }

        basic_iterator& operator++() {
            node_ptr_type node = stack_.top();
            stack_.pop();
            if (node->getRightChild()) {
                push_left(node->getRightChild().get());
            }
            return *this;
        }
        basic_iterator operator++(int) {
            basic_iterator tmp = *this;
            ++*this;
            return tmp;
        }

        basic_iterator& operator--() {
            if (stack_.empty()) {
                return *this;
            }
            node_ptr_type node = stack_.top();
            if (node->getLeftChild()) {
                node = node->getLeftChild().get();
                while (node->getRightChild()) {
                    node = node->getRightChild().get();
                }
                stack_.push(node);
            } else {
                node_ptr_type last = node;
                stack_.pop();
                while (!stack_.empty() &&
                       stack_.top()->getRightChild().get() == last) {
                    last = stack_.top();
                    stack_.pop();
                }
                if (!stack_.empty())
                    stack_.push(stack_.top());
            }
            return *this;
        }
        basic_iterator operator--(int) {
            basic_iterator tmp = *this;
            --*this;
            return tmp;
        }

        bool operator==(basic_iterator const& iterator) const {
            if (stack_.empty() && iterator.stack_.empty())
                return true;
            if (stack_.empty() || iterator.stack_.empty())
                return false;
            return stack_.top() == iterator.stack_.top();
        }
        bool operator!=(basic_iterator const& iterator) const {
            return !(*this == iterator);
        }
    };

    using iterator = basic_iterator<false>;
    using const_iterator = basic_iterator<true>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    bool operator==(AVLTree const& tree) const;
    bool operator!=(AVLTree const& tree) const;

    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool empty() const;
    void insert(const node_type& value);
    void erase(const node_type& value);
    [[nodiscard]] bool contains(const node_type& value) const;
    [[nodiscard]] bool balanced() const;

    [[nodiscard]] size_t findDistance(const node_type& lower_key,
                                      const node_type& upper_key) const;

    std::vector<node_type> getElements() const;
    void dump(std::ostream& ostr = std::cout) const;
    void dumpgv(std::ostream& ostr = std::cout) const;

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
    bool balanced(const_iterator node_it) const;

    size_t findNumOfLarge(const node_type& value,
                          const std::unique_ptr<Node<node_type>>& node) const;
    size_t findNumOfSmaller(const node_type& value,
                            const std::unique_ptr<Node<node_type>>& node) const;
    size_t findNumOfLarge(const node_type& value) const;
    size_t findNumOfSmaller(const node_type& value) const;
};

}  // namespace SearchTree