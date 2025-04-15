#include <benchmark/benchmark.h>

#include <set>
#include <fstream>

#include "tree.hpp"

template <typename T>
void runBenchmaerk() {
    T tree{};
    char command;

    std::ifstream test_file;
    std::string file_path = std::string(TEST_FILES_DIR) + "/test_input14.txt";
    test_file.open(file_path);
    if (!test_file.is_open()) {
        throw std::runtime_error("\n Failed to open the file: " + file_path);
    }

    while (test_file >> command) {
        switch (command) {
            case 'k': {
                int n;
                test_file >> n;
                tree.insert(n);
                break;
            }
            case 'q': {
                int a;
                int b;
                test_file >> a >> b;
                if constexpr(std::is_same_v<T, SearchTree::AVLTree>) {
                    tree.findDistance(a, b);
                }
                else {
                    if(a > b) {
                        continue;
                    }
                    std::distance(tree.lower_bound(a), tree.upper_bound(b));
                }
                break;
            }
            default:
                std::cerr << "Unknown command\n";
        }
    }
    test_file.close();
}

static void BM_Tree(benchmark::State& state) {
    for (auto _ : state) {
        runBenchmaerk<SearchTree::AVLTree>();
    }
}

static void BM_Set(benchmark::State& state) {
    for (auto _ : state) {
        runBenchmaerk<std::set<int>>();
    }
}

BENCHMARK(BM_Tree)->Iterations(1);
BENCHMARK(BM_Set)->Iterations(1);

BENCHMARK_MAIN();