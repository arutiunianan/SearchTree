#include <chrono>

#include "tree.hpp"

int main() {
    SearchTree::AVLTree<int> tree{};
    char command;

    std::chrono::duration<double> duration = std::chrono::duration<double>::zero();
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

                int b;
                std::cin >> b;
                auto start = std::chrono::high_resolution_clock::now();
                (void)tree.findDistance(a, b);
                auto end = std::chrono::high_resolution_clock::now();
                duration = duration + (end - start);
                break;
            }
        }
    }
    std::cout << duration.count();
}