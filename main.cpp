#include "tree.hpp"

int main() {
    SearchTree::AVLTree<int> tree{};
    char command;

    try {
        while (std::cin >> command) {
            switch (command) {
                case 'k': {
                    int n;
                    std::cin >> n;
                    if (!std::cin.good()) {
                        throw std::invalid_argument("\n Invalid key");
                    }

                    tree.insert(n);
                    break;
                }
                case 'q': {
                    int a;
                    std::cin >> a;
                    if (!std::cin.good()) {
                        throw std::invalid_argument(
                            "\n Invalid first number for the request");
                    }

                    int b;
                    std::cin >> b;
                    if (!std::cin.good()) {
                        throw std::invalid_argument(
                            "\n Invalid second number for the request");
                    }

                    std::cout << tree.findDistance(a, b) << std::endl;
                    break;
                }
                default:
                    throw std::invalid_argument("\n Unknown command");
            }
        }
    } catch (const SearchTree::AVLException& e) {
        std::cerr << "Tree error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception :(" << std::endl;
    }
}