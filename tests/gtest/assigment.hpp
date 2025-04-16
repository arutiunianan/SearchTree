#pragma once

#include <gtest/gtest.h>
#include <sstream>

#include "tree.hpp"

template <typename T>
std::vector<int> runTest(std::istringstream& input) {
    T tree{};
    char command;
    std::vector<int> answer;

    while (input >> command) {
        switch (command) {
            case 'k': {
                int n;
                input >> n;
                tree.insert(n);
                break;
            }
            case 'q': {
                int a;
                int b;
                input >> a >> b;
                if constexpr (std::is_same_v<T, SearchTree::AVLTree>) {
                    answer.push_back(tree.findDistance(a, b));
                } else {
                    if (a > b) {
                        answer.push_back(0);
                    } else {
                        answer.push_back(std::distance(tree.lower_bound(a),
                                                       tree.upper_bound(b)));
                    }
                }
                break;
            }
            default:
                std::cerr << "Unknown command\n";
        }
    }
    return answer;
}

TEST(AVLTree_Assignment, Subtestv_1) {
    std::string input = "k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_2) {
    std::string input = "";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_3) {
    std::string input = "k 5 k 10 k 15 k 20";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_4) {
    std::string input = "k 100 q 50 150";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_5) {
    std::string input = "k 10 k 20 q 30 15 q 20 20";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_6) {
    std::string input = "k 10 k 5 q 1 20 k 15 q 10 16 k 25 q 20 30";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_7) {
    std::string input = "k 50 k 40 k 30 k 20 k 10 q 10 50";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_8) {
    std::string input = "k 10 k 10 k 20 k 20 q 5 25";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_9) {
    std::string input = "k 5 k 10 k 15 k 20 k 25 q 0 30 q 10 20 q 6 16";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_10) {
    std::string input = "k -20 k -10 k 0 k 10 k 20 q -15 5 q -25 -5";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_11) {
    std::ostringstream oss;
    for (int i = 1; i <= 100; ++i) {
        oss << "k " << i << " ";
    }
    oss << "q 10 20 q 1 100 q 50 101";
    std::string input = oss.str();
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_12) {
    std::string input =
        "k 42 k 7 q 5 15 k 85 q 40 90 k 23 k 56 q 20 60 k 99 q 50 110";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_13) {
    std::string input = "k 100 q 50 150 q 100 200 q 1 100";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_14) {
    std::string input = "q 10 20 k 15 q 10 20 k 25 q 20 30";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_15) {
    std::string input =
        "k 5 k 10 q 1 15 k 3 k 7 q 5 10 k 20 q 0 100 k 1 k 4 q 2 8";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_16) {
    std::ostringstream oss;
    for (int i = 1; i <= 50; ++i)
        oss << "k " << i << " ";
    oss << "q 10 20 q 1 51 q 25 30";
    std::string input = oss.str();
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_17) {
    std::string input = "q 10 20 q 0 100 q 5 15";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_18) {
    std::string input = "k 10 k 20 q 5 25 q 10 20 k 30 q 15 35 q 10 40 q 0 100";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_19) {
    std::string input =
        "k " + std::to_string(std::numeric_limits<int>::min()) + " k 0 k " +
        std::to_string(std::numeric_limits<int>::max()) + " q " +
        std::to_string(std::numeric_limits<int>::min()) + " " +
        std::to_string(std::numeric_limits<int>::max());
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_20) {
    std::string input = "k 5 k 10 k 15 k 5 k 10 k 15 q 1 20";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_21) {
    std::ostringstream oss;
    for (int i = 1; i <= 20; ++i) {
        oss << "k " << i << " q " << i - 1 << " " << i + 1 << " ";
    }
    std::string input = oss.str();
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_22) {
    std::string input =
        "k 1000 k 5000 k 10000 k 20000 q 1000 10000 q 5000 30000";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_23) {
    std::string input = "k 10 k 20 k 30 k 40 q 20 20 q 10 10 q 30 30";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_24) {
    std::string input =
        "k -100 k -50 k 0 k 50 k 100 q -75 25 q -150 -25 q 25 150";
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}

TEST(AVLTree_Assignment, Subtestv_25) {
    std::ostringstream oss;
    for (int i = 1; i <= 200; ++i) {
        oss << "k " << i * 3 << " ";
        if (i % 10 == 0)
            oss << "q " << i * 3 - 20 << " " << i * 3 + 20 << " ";
    }
    oss << "q 50 600";
    std::string input = oss.str();
    std::istringstream iss_avl(input), iss_set(input);
    auto resultAVL = runTest<SearchTree::AVLTree>(iss_avl);
    auto resultStd = runTest<std::set<int>>(iss_set);
    ASSERT_EQ(resultAVL, resultStd);
}