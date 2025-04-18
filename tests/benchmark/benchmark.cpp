#include <benchmark/benchmark.h>
#include <filesystem>
#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "tree.hpp"

namespace fs = std::filesystem;

template <typename T>
void runTest(const std::string& file_path) {
    T tree;
    char command;
    std::ifstream test_file(file_path);
    if (!test_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
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
                int a, b;
                test_file >> a >> b;
                if constexpr (std::is_same_v<T, SearchTree::AVLTree>) {
                    (void)tree.findDistance(a, b);
                } else {
                    if (a <= b) {
                        (void)std::distance(tree.lower_bound(a),
                                            tree.upper_bound(b));
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}

int main(int argc, char** argv) {
    std::vector<fs::path> files;
    for (auto& entry : fs::directory_iterator(TEST_FILES_DIR)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            files.push_back(entry.path());
        }
    }
    //std::sort(files.begin(), files.end());

    for (auto& path : files) {
        auto filename = path.filename().string();
        int test_num = 0;
        size_t p = filename.find("test_input");
        if (p != std::string::npos) {
            p += strlen("test_input");
            size_t q = filename.find('.', p);
            test_num = std::stoi(filename.substr(p, q - p));
        }
        std::string name_tree = "AVLTree/TEST" + std::to_string(test_num);
        std::string name_set = "std::set/TEST" + std::to_string(test_num);

        benchmark::RegisterBenchmark(name_tree.c_str(), [path](benchmark::State&
                                                                   state) {
            for (auto _ : state)
                runTest<SearchTree::AVLTree>(path.string());
        })->Iterations(1);

        benchmark::RegisterBenchmark(name_set.c_str(), [path](benchmark::State&
                                                                  state) {
            for (auto _ : state)
                runTest<std::set<int>>(path.string());
        })->Iterations(1);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
