#include "tree.hpp"

int main() {
    SearchTree::AVLTree tree{};
    char command;

    while (std::cin >> command) {
        switch (command) {
            case 'k': {
                int n;
                std::cin >> n;
                tree.insert(n);
                break;
            }
            case 'q': {
                int a;
                int b;
                std::cin >> a >> b;
                std::cout << tree.findDistance(a, b) << std::endl;
                break;
            }
            default:
                std::cerr << "Unknown command\n";
                return 1;
        }
    }
    return 0;
}