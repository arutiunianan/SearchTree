#include "tree.hpp"

namespace SearchTree {

size_t AVLTree::findDistance(const node_type& lower_key,
                             const node_type& upper_key) const {
    if (empty() || lower_key > upper_key) {
        return 0;
    }

    size_t num_of_nodes = Node<node_type>::computeDescNum(root);
    size_t num_of_large = findNumOfLarge(lower_key);
    size_t num_of_smaller = findNumOfSmaller(upper_key);
    return num_of_large + num_of_smaller - num_of_nodes;
}

size_t AVLTree::findNumOfLarge(const node_type& value) const {
    return findNumOfLarge(value, root);
}
size_t AVLTree::findNumOfLarge(
    const node_type& value,
    const std::unique_ptr<Node<node_type>>& node) const {
    if (!node) {
        throw NodeNullException();
    }

    size_t num_of_large = 0;
    if (node->getValue() >= value) {
        if (node->getRightChild()) {
            num_of_large +=
                Node<node_type>::computeDescNum(node->getRightChild());
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

size_t AVLTree::findNumOfSmaller(const node_type& value) const {
    return findNumOfSmaller(value, root);
}
size_t AVLTree::findNumOfSmaller(
    const node_type& value,
    const std::unique_ptr<Node<node_type>>& node) const {
    if (!node) {
        throw NodeNullException();
    }

    size_t num_of_smaller = 0;

    if (node->getValue() <= value) {
        if (node->getLeftChild()) {
            num_of_smaller +=
                Node<node_type>::computeDescNum(node->getLeftChild());
        }
        if (node->getRightChild()) {
            num_of_smaller += findNumOfSmaller(value, node->getRightChild());
        }
        ++num_of_smaller;
    } else {
        if (node->getLeftChild()) {
            num_of_smaller += findNumOfSmaller(value, node->getLeftChild());
        }
    }

    return num_of_smaller;
}

void AVLTree::balance(std::unique_ptr<Node<node_type>>& node) {
    if (!node) {
        throw NodeNullException();
    }

    size_t left_height = Node<node_type>::computeHeight(node->getLeftChild());
    size_t right_height = Node<node_type>::computeHeight(node->getRightChild());

    if (right_height >= left_height + 2) {
        balanceRight(node);
    } else if (left_height >= right_height + 2) {
        balanceLeft(node);
    }
}

void AVLTree::balanceRight(std::unique_ptr<Node<node_type>>& node) {
    if (!node) {
        throw NodeNullException();
    }

    std::unique_ptr<Node<node_type>> right_subtree =
        std::move(node->getRightChild());
    if (Node<node_type>::computeHeight(right_subtree->getLeftChild()) <=
        Node<node_type>::computeHeight(right_subtree->getRightChild())) {
        node->getRightChild() = std::move(right_subtree->getLeftChild());
        node->updateParameters();
        right_subtree->getLeftChild() = std::move(node);
        right_subtree->updateParameters();
        std::swap(right_subtree, node);
    } else {
        std::unique_ptr<Node<node_type>> pivot_node =
            std::move(right_subtree->getLeftChild());
        node->getRightChild() = std::move(pivot_node->getLeftChild());
        node->updateParameters();
        right_subtree->getLeftChild() = std::move(pivot_node->getRightChild());
        right_subtree->updateParameters();
        pivot_node->getLeftChild() = std::move(node);
        pivot_node->getRightChild() = std::move(right_subtree);
        pivot_node->updateParameters();
        std::swap(pivot_node, node);
    }
}

void AVLTree::balanceLeft(std::unique_ptr<Node<node_type>>& node) {
    if (!node) {
        throw NodeNullException();
    }

    std::unique_ptr<Node<node_type>> left_subtree =
        std::move(node->getLeftChild());
    if (Node<node_type>::computeHeight(left_subtree->getRightChild()) <=
        Node<node_type>::computeHeight(left_subtree->getLeftChild())) {
        node->getLeftChild() = std::move(left_subtree->getRightChild());
        node->updateParameters();
        left_subtree->getRightChild() = std::move(node);
        left_subtree->updateParameters();
        std::swap(left_subtree, node);
    } else {
        std::unique_ptr<Node<node_type>> pivot_node =
            std::move(left_subtree->getRightChild());
        node->getLeftChild() = std::move(pivot_node->getRightChild());
        node->updateParameters();
        left_subtree->getRightChild() = std::move(pivot_node->getLeftChild());
        left_subtree->updateParameters();
        pivot_node->getRightChild() = std::move(node);
        pivot_node->getLeftChild() = std::move(left_subtree);
        pivot_node->updateParameters();
        std::swap(pivot_node, node);
    }
}

bool AVLTree::balanced() const {
    for (auto it = begin(); it != end(); ++it) {
        if (!balanced(it)) {
            return false;
        }
    }
    return true;
}
bool AVLTree::balanced(const_iterator node_it) const {
    size_t left_height =
        Node<node_type>::computeHeight(node_it->getLeftChild());
    size_t right_height =
        Node<node_type>::computeHeight(node_it->getRightChild());

    if ((left_height >= 2 + right_height) ||
        (right_height >= 2 + left_height)) {
        return false;
    }
    return true;
}

AVLTree::iterator AVLTree::begin() {
    return iterator(root.get());
}
AVLTree::iterator AVLTree::end() {
    return iterator();
}
AVLTree::const_iterator AVLTree::begin() const {
    return const_iterator(root.get());
}
AVLTree::const_iterator AVLTree::end() const {
    return const_iterator();
}
AVLTree::const_iterator AVLTree::cbegin() const {
    return const_iterator(root.get());
}
AVLTree::const_iterator AVLTree::cend() const {
    return const_iterator();
}

size_t AVLTree::size() const {
    return Node<node_type>::computeDescNum(root);
}
bool AVLTree::empty() const {
    return !size();
}

void AVLTree::insert(const node_type& value) {
    if (empty()) {
        root = std::make_unique<Node<node_type>>(value);
        return;
    }
    insert(value, root);
}
void AVLTree::insert(const node_type& value,
                     std::unique_ptr<Node<node_type>>& node) {
    if (!node) {
        throw NodeNullException();
    }

    if (node->getValue() > value) {
        if (!(node->getLeftChild())) {
            node->addLeftChild(value);
        } else {
            insert(value, node->getLeftChild());
        }
    } else if (node->getValue() < value) {
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

void AVLTree::erase(const node_type& value) {
    if (empty()) {
        return;
    }
    erase(value, root);
}
void AVLTree::erase(const node_type& value,
                    std::unique_ptr<Node<node_type>>& node) {
    if (!node) {
        throw NodeNullException();
    }

    if (value < node->getValue()) {
        if (!(node->getLeftChild())) {
            return;
        }
        erase(value, node->getLeftChild());
    } else if (value > node->getValue()) {
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
            if (Node<node_type>::computeHeight(node->getLeftChild()) >
                Node<node_type>::computeHeight(node->getRightChild())) {
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

bool AVLTree::contains(const node_type& value) const {
    return contains(value, root);
}
bool AVLTree::contains(const node_type& value,
                       const std::unique_ptr<Node<node_type>>& node) const {
    if (!node) {
        return false;
    }

    if (value < node->getValue()) {
        return contains(value, node->getLeftChild());
    } else if (value > node->getValue()) {
        return contains(value, node->getRightChild());
    }
    return true;
}

AVLTree::node_type AVLTree::min(std::unique_ptr<Node<node_type>>& node) const {
    if (!node) {
        throw NodeNullException();
    }

    if (!node->getLeftChild()) {
        return node->getValue();
    }
    return min(node->getLeftChild());
}

AVLTree::node_type AVLTree::max(std::unique_ptr<Node<node_type>>& node) const {
    if (!node) {
        throw NodeNullException();
    }

    if (!node->getRightChild()) {
        return node->getValue();
    }
    return max(node->getRightChild());
}

std::vector<AVLTree::node_type> AVLTree::getElements() const {
    if (empty()) {
        return std::vector<node_type>{};
    }

    std::vector<node_type> elements;
    for (auto it = begin(); it != end(); ++it) {
        elements.push_back(it->getValue());
    }
    return elements;
}

bool AVLTree::operator==(AVLTree const& tree) const {
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

bool AVLTree::operator!=(AVLTree const& tree) const {
    return !(*this == tree);
}

void AVLTree::dump(std::ostream& ostr) const {
    if (empty()) {
        throw EmptyTreeException();
    }

    for (auto it = begin(); it != end(); ++it) {
        it->dump(ostr);
    }
}

void AVLTree::dumpgv(std::ostream& ostr) const {
    if (empty()) {
        throw EmptyTreeException();
    }
    ostr << "digraph structs {\n";
    root->dumpgv(ostr);
    ostr << "}";
}

}  // namespace SearchTree