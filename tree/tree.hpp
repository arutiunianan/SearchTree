#pragma once

#include <functional>
#include <iterator>
#include <stack>
#include <utility>
#include <vector>

#include "node.hpp"
#include "tree_exception.hpp"

namespace SearchTree {

template <typename T>
class AVLTree final {
   private:
    std::unique_ptr<Node<T>> root;

   public:
    AVLTree() = default;
    explicit AVLTree(T root_value)
        : root(std::make_unique<Node<T>>(root_value)) {}

    //----------------------------------iterators----------------------------------
    template <bool is_const>
    class basic_iterator {
       private:
        using node_ptr_type =
            std::conditional_t<is_const, const Node<T>*, Node<T>*>;
        std::stack<node_ptr_type> stack_;

        void push_left(node_ptr_type node) {
            while (node) {
                stack_.push(node);
                node = node->getLeftChild().get();
            }
        }

       public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Node<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = node_ptr_type;
        using reference =
            std::conditional_t<is_const, const Node<T>&, Node<T>&>;

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

    iterator begin() { return iterator(root.get()); }

    iterator end() { return iterator(); }

    const_iterator begin() const { return const_iterator(root.get()); }

    const_iterator end() const { return const_iterator(); }

    const_iterator cbegin() const { return const_iterator(root.get()); }

    const_iterator cend() const { return const_iterator(); }

    //----------------------------------basic operations----------------------------------

    bool operator==(AVLTree const& tree) const {
        if (!root && !(tree.root)) {
            return true;
        }

        if (!root || !(tree.root)) {
            return false;
        }

        if (*root == *(tree.root)) {
            return true;
        }
        return false;
    }

    bool operator!=(AVLTree const& tree) const { return !(*this == tree); }

    [[nodiscard]] size_t size() const { return Node<T>::computeDescNum(root); }

    [[nodiscard]] bool empty() const { return !size(); }

    void insert(const T& value) {
        if (empty()) {
            root = std::make_unique<Node<T>>(value);
            return;
        }
        insert(value, root);
    }

    void erase(const T& value) {
        if (empty()) {
            return;
        }
        erase(value, root);
    }

    [[nodiscard]] bool contains(const T& value) const {
        return contains(value, root);
    }

    [[nodiscard]] bool balanced() const {
        for (auto it = begin(); it != end(); ++it) {
            if (!balanced(it)) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] size_t findDistance(const T& lower_key,
                                      const T& upper_key) const {
        if (empty() || std::greater<>{}(lower_key, upper_key)) {
            return 0;
        }

        size_t num_of_nodes = Node<T>::computeDescNum(root);
        size_t num_of_large = findNumOfLarge(lower_key);
        size_t num_of_smaller = findNumOfSmaller(upper_key);
        return num_of_large + num_of_smaller - num_of_nodes;
    }

    std::vector<T> getElements() const {
        if (empty()) {
            return std::vector<T>{};
        }

        std::vector<T> elements;
        for (auto it = begin(); it != end(); ++it) {
            elements.push_back(it->getValue());
        }
        return elements;
    }

    void dump(std::ostream& ostr = std::cout) const {
        if (empty()) {
            throw EmptyTreeException();
        }

        for (auto it = begin(); it != end(); ++it) {
            it->dump(ostr);
        }
    }

    void dumpgv(std::ostream& ostr = std::cout) const {
        if (empty()) {
            throw EmptyTreeException();
        }

        graphviz graph{};
        root->dumpgv(graph, graphviz_formatter::root_node);
        graph.print(ostr);
    }

   private:
    void insert(const T& value, std::unique_ptr<Node<T>>& node) {
        if (!node) {
            throw NodeNullException();
        }

        if (std::greater<>{}(node->getValue(), value)) {
            if (!(node->getLeftChild())) {
                node->addLeftChild(value);
            } else {
                insert(value, node->getLeftChild());
            }
        } else if (std::less<>{}(node->getValue(), value)) {
            if (!(node->getRightChild())) {
                node->addRightChild(value);
            } else {
                insert(value, node->getRightChild());
            }
        } else {
            return;
        }

        node->updateParameters();
        balance(node);
    }

    void erase(const T& value, std::unique_ptr<Node<T>>& node) {
        if (!node) {
            throw NodeNullException();
        }

        if (std::less<>{}(value, node->getValue())) {
            if (!(node->getLeftChild())) {
                return;
            }
            erase(value, node->getLeftChild());
        } else if (std::greater<>{}(value, node->getValue())) {
            if (!(node->getRightChild())) {
                return;
            }
            erase(value, node->getRightChild());
        } else {
            if (!node->getLeftChild()) {
                node = std::move(node->getRightChild());
            } else if (!node->getRightChild()) {
                node = std::move(node->getLeftChild());
            } else {
                if (Node<T>::computeHeight(node->getLeftChild()) >
                    Node<T>::computeHeight(node->getRightChild())) {
                    node->addValue(max(node->getLeftChild()));
                    erase(node->getValue(), node->getLeftChild());
                } else {
                    node->addValue(min(node->getRightChild()));
                    erase(node->getValue(), node->getRightChild());
                }
            }
        }

        if (node) {
            node->updateParameters();
            balance(node);
        }
    }

    bool contains(const T& value, const std::unique_ptr<Node<T>>& node) const {
        if (!node) {
            return false;
        }

        if (std::less<>{}(value, node->getValue())) {
            return contains(value, node->getLeftChild());
        } else if (std::greater<>{}(value, node->getValue())) {
            return contains(value, node->getRightChild());
        }
        return true;
    }

    T min(std::unique_ptr<Node<T>>& node) const {
        if (!node) {
            throw NodeNullException();
        }

        if (!node->getLeftChild()) {
            return node->getValue();
        }
        return min(node->getLeftChild());
    }

    T max(std::unique_ptr<Node<T>>& node) const {
        if (!node) {
            throw NodeNullException();
        }

        if (!node->getRightChild()) {
            return node->getValue();
        }
        return max(node->getRightChild());
    }

    //----------------------------------operations for task----------------------------------

    void balance(std::unique_ptr<Node<T>>& node) {
        if (!node) {
            throw NodeNullException();
        }

        size_t left_height = Node<T>::computeHeight(node->getLeftChild());
        size_t right_height = Node<T>::computeHeight(node->getRightChild());

        if (right_height >= left_height + 2) {
            balanceRight(node);
        } else if (left_height >= right_height + 2) {
            balanceLeft(node);
        }
    }

    void balanceLeft(std::unique_ptr<Node<T>>& node) {
        if (!node) {
            throw NodeNullException();
        }

        std::unique_ptr<Node<T>> left_subtree = std::move(node->getLeftChild());
        if (Node<T>::computeHeight(left_subtree->getRightChild()) <=
            Node<T>::computeHeight(left_subtree->getLeftChild())) {
            node->getLeftChild() = std::move(left_subtree->getRightChild());
            node->updateParameters();
            left_subtree->getRightChild() = std::move(node);
            left_subtree->updateParameters();
            std::swap(left_subtree, node);
        } else {
            std::unique_ptr<Node<T>> pivot_node =
                std::move(left_subtree->getRightChild());
            node->getLeftChild() = std::move(pivot_node->getRightChild());
            node->updateParameters();
            left_subtree->getRightChild() =
                std::move(pivot_node->getLeftChild());
            left_subtree->updateParameters();
            pivot_node->getRightChild() = std::move(node);
            pivot_node->getLeftChild() = std::move(left_subtree);
            pivot_node->updateParameters();
            std::swap(pivot_node, node);
        }
    }

    void balanceRight(std::unique_ptr<Node<T>>& node) {
        if (!node) {
            throw NodeNullException();
        }

        std::unique_ptr<Node<T>> right_subtree =
            std::move(node->getRightChild());
        if (Node<T>::computeHeight(right_subtree->getLeftChild()) <=
            Node<T>::computeHeight(right_subtree->getRightChild())) {
            node->getRightChild() = std::move(right_subtree->getLeftChild());
            node->updateParameters();
            right_subtree->getLeftChild() = std::move(node);
            right_subtree->updateParameters();
            std::swap(right_subtree, node);
        } else {
            std::unique_ptr<Node<T>> pivot_node =
                std::move(right_subtree->getLeftChild());
            node->getRightChild() = std::move(pivot_node->getLeftChild());
            node->updateParameters();
            right_subtree->getLeftChild() =
                std::move(pivot_node->getRightChild());
            right_subtree->updateParameters();
            pivot_node->getLeftChild() = std::move(node);
            pivot_node->getRightChild() = std::move(right_subtree);
            pivot_node->updateParameters();
            std::swap(pivot_node, node);
        }
    }

    bool balanced(const_iterator node_it) const {
        size_t left_height = Node<T>::computeHeight(node_it->getLeftChild());
        size_t right_height = Node<T>::computeHeight(node_it->getRightChild());

        if ((left_height >= 2 + right_height) ||
            (right_height >= 2 + left_height)) {
            return false;
        }
        return true;
    }

    size_t findNumOfLarge(const T& value) const {
        return findNumOfLarge(value, root);
    }
    size_t findNumOfLarge(const T& value,
                          const std::unique_ptr<Node<T>>& node) const {
        if (!node) {
            throw NodeNullException();
        }

        size_t num_of_large = 0;
        if (std::greater_equal<>{}(node->getValue(), value)) {
            if (node->getRightChild()) {
                num_of_large += Node<T>::computeDescNum(node->getRightChild());
            }
            if (node->getLeftChild()) {
                num_of_large += findNumOfLarge(value, node->getLeftChild());
            }
            ++num_of_large;
        } else {
            if (node->getRightChild()) {
                num_of_large += findNumOfLarge(value, node->getRightChild());
            }
        }

        return num_of_large;
    }

    size_t findNumOfSmaller(const T& value) const {
        return findNumOfSmaller(value, root);
    }
    size_t findNumOfSmaller(const T& value,
                            const std::unique_ptr<Node<T>>& node) const {
        if (!node) {
            throw NodeNullException();
        }

        size_t num_of_smaller = 0;

        if (std::less_equal<>{}(node->getValue(), value)) {
            if (node->getLeftChild()) {
                num_of_smaller += Node<T>::computeDescNum(node->getLeftChild());
            }
            if (node->getRightChild()) {
                num_of_smaller +=
                    findNumOfSmaller(value, node->getRightChild());
            }
            ++num_of_smaller;
        } else {
            if (node->getLeftChild()) {
                num_of_smaller += findNumOfSmaller(value, node->getLeftChild());
            }
        }

        return num_of_smaller;
    }
};

}  // namespace SearchTree