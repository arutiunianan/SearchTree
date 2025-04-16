#pragma once

#include <gtest/gtest.h>

#include "tree.hpp"

void checkTreeInsert(const std::vector<int>& testNumbers) {
    SearchTree::AVLTree tree{};
    for (int num : testNumbers) {
        tree.insert(num);
    }

    std::set<int> set(testNumbers.begin(), testNumbers.end());
    std::vector<int> expected(set.begin(), set.end());
    ASSERT_EQ(tree.getElements(), expected);
    ASSERT_TRUE(tree.balanced());
}

TEST(AVLTree_insert, Subtestv_1) {
    checkTreeInsert({10, 5, 15});
}

TEST(AVLTree_insert, Subtestv_2) {
    checkTreeInsert({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
}

TEST(AVLTree_insert, Subtestv_3) {
    checkTreeInsert({10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
}

TEST(AVLTree_insert, Subtestv_4) {
    checkTreeInsert({15, 3, 8, 22, 17, 5, 11, 30});
}

TEST(AVLTree_insert, Subtestv_5) {
    checkTreeInsert({15, 3, 8, 22, 17, 5, 11, 30});
}

TEST(AVLTree_insert, Subtestv_6) {
    checkTreeInsert({30, 25, 20, 15, 10, 5});
}

TEST(AVLTree_insert, Subtestv_7) {
    checkTreeInsert({5, 10, 15, 20, 25, 30});
}

TEST(AVLTree_insert, Subtestv_8) {
    checkTreeInsert({20, 10, 30, 5, 15, 25, 35});
}

TEST(AVLTree_insert, Subtestv_9) {
    checkTreeInsert({-10, -5, 0, 5, 10});
}

TEST(AVLTree_insert, Subtestv_10) {
    checkTreeInsert({});
}

TEST(AVLTree_insert, Subtestv_11) {
    checkTreeInsert({100, 300, 700, 1500, 3200});
}

TEST(AVLTree_insert, Subtestv_12) {
    checkTreeInsert({0, 0, 0, 0, 0});
}

TEST(AVLTree_insert, Subtestv_13) {
    std::vector<int> testNumbers;
    for (int i = 0; i < 1000; i++) {
        testNumbers.push_back(i);
    }
    checkTreeInsert(testNumbers);
}

TEST(AVLTree_insert, Subtestv_14) {
    checkTreeInsert(
        {std::numeric_limits<int>::min(), 0, std::numeric_limits<int>::max()});
}

TEST(AVLTree_insert, Subtestv_15) {
    checkTreeInsert({50, 20, 70, 10, 30, 60, 80, 5, 15, 25, 35});
}

TEST(AVLTree_operator_eq, Subtestv_1) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    ASSERT_TRUE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_2) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    tree1.insert(10);
    tree2.insert(10);
    ASSERT_TRUE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_3) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    tree1.insert(10);
    tree2.insert(15);
    ASSERT_FALSE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_4) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    tree1.insert(10);
    tree1.insert(20);
    tree2.insert(10);
    ASSERT_FALSE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_5) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    tree1.insert(10);
    tree1.insert(20);
    tree2.insert(10);
    tree2.insert(25);
    ASSERT_FALSE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_6) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    for (int v : {10, 5, 15, 3, 7, 12, 18}) {
        tree1.insert(v);
        tree2.insert(v);
    }
    tree1.erase(7);
    tree2.erase(7);
    ASSERT_TRUE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_7) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    for (int v : {10, 5, 15, 3, 7, 12, 18}) {
        tree1.insert(v);
        tree2.insert(v);
    }
    tree1.erase(7);
    tree2.erase(7);
    ASSERT_TRUE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_8) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    for (int v : {10, 5, 15, 3, 7, 12, 18}) {
        tree1.insert(v);
        tree2.insert(v);
    }
    tree1.erase(7);
    ASSERT_FALSE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_9) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    for (int v : {20, 10, 30, 5, 15, 25, 35}) {
        tree1.insert(v);
        tree2.insert(v);
    }
    tree1.erase(25);
    tree2.erase(25);
    tree1.insert(27);
    tree2.insert(27);
    ASSERT_TRUE(tree1 == tree2);
}

TEST(AVLTree_operator_eq, Subtestv_10) {
    SearchTree::AVLTree tree1;
    SearchTree::AVLTree tree2;
    tree2.insert(10);
    ASSERT_FALSE(tree1 == tree2);
}

void checkTreeAfterErase(const std::vector<int>& insertNumbers,
                         const std::vector<int>& eraseNumbers) {
    SearchTree::AVLTree tree;
    for (int v : insertNumbers) {
        tree.insert(v);
    }
    for (int v : eraseNumbers) {
        tree.erase(v);
    }
    std::set<int> set(insertNumbers.begin(), insertNumbers.end());
    for (int v : eraseNumbers) {
        set.erase(v);
    }
    std::vector<int> expected(set.begin(), set.end());
    ASSERT_EQ(tree.getElements(), expected);
    ASSERT_TRUE(tree.balanced());
}

TEST(AVLTree_erase, Subtestv_1) {
    checkTreeAfterErase({10, 5, 15, 3, 7}, {3});
}

TEST(AVLTree_erase, Subtestv_2) {
    checkTreeAfterErase({10}, {10});
}

TEST(AVLTree_erase, Subtestv_3) {
    checkTreeAfterErase({10}, {15});
}

TEST(AVLTree_erase, Subtestv_4) {
    checkTreeAfterErase({20, 10, 30, 5}, {10});
}

TEST(AVLTree_erase, Subtestv_5) {
    checkTreeAfterErase({20, 10, 30, 5, 15}, {10});
}

TEST(AVLTree_erase, Subtestv_6) {
    checkTreeAfterErase({50, 20, 70, 10, 30, 60, 80}, {10, 80});
}

TEST(AVLTree_erase, Subtestv_7) {
    checkTreeAfterErase({10, 20, 30}, {10, 20, 30});
}

TEST(AVLTree_erase, Subtestv_8) {
    checkTreeAfterErase({}, {10, 20, 30});
}

TEST(AVLTree_erase, Subtestv_9) {
    checkTreeAfterErase({10, 10, 10, 20, 30}, {10});
}

TEST(AVLTree_erase, Subtestv_10) {
    checkTreeAfterErase({50, 40, 60, 30, 45, 55, 70}, {40, 70, 55, 90});
}

TEST(AVLTree_contains, Subtestv_1) {
    SearchTree::AVLTree tree;
    ASSERT_FALSE(tree.contains(10));
}

TEST(AVLTree_contains, Subtestv_2) {
    SearchTree::AVLTree tree;
    tree.insert(10);
    ASSERT_TRUE(tree.contains(10));
}

TEST(AVLTree_contains, Subtestv_3) {
    SearchTree::AVLTree tree;
    tree.insert(10);
    ASSERT_FALSE(tree.contains(15));
}

TEST(AVLTree_contains, Subtestv_4) {
    SearchTree::AVLTree tree;
    for (int v : {10, 5, 15, 3, 7}) {
        tree.insert(v);
    }
    ASSERT_TRUE(tree.contains(7));
}

TEST(AVLTree_contains, Subtestv_5) {
    SearchTree::AVLTree tree;
    for (int v : {10, 5, 15, 3, 7}) {
        tree.insert(v);
    }
    ASSERT_FALSE(tree.contains(20));
}

TEST(AVLTree_contains, Subtestv_6) {
    SearchTree::AVLTree tree;
    for (int v : {20, 10, 30}) {
        tree.insert(v);
    }
    tree.erase(10);
    ASSERT_FALSE(tree.contains(10));
}

TEST(AVLTree_contains, Subtestv_7) {
    SearchTree::AVLTree tree;
    tree.insert(25);
    tree.erase(25);
    tree.insert(25);
    ASSERT_TRUE(tree.contains(25));
}

TEST(AVLTree_contains, Subtestv_8) {
    SearchTree::AVLTree tree;
    for (int i = 0; i < 1000; ++i) {
        tree.insert(i);
    }
    ASSERT_TRUE(tree.contains(500));
}

TEST(AVLTree_contains, Subtestv_9) {
    SearchTree::AVLTree tree;
    tree.insert(std::numeric_limits<int>::min());
    ASSERT_TRUE(tree.contains(std::numeric_limits<int>::min()));
}

TEST(AVLTree_contains, Subtest_10) {
    SearchTree::AVLTree tree;
    tree.insert(std::numeric_limits<int>::max());
    ASSERT_TRUE(tree.contains(std::numeric_limits<int>::max()));
}