#include <AVLTree.h>
#include <crtdbg.h>
#include <fmt/format.h>
#include <gtest/gtest.h>

#include "AVLTree.h"

TEST(AVLTest, Rotation) {
    auto tree = Tree::AVL<int, int>();
    tree.Insert({1, 1});
    tree.Insert({2, 2});
    tree.Insert({3, 4});
    ASSERT_EQ(tree.Root()->Key(), 2);
    ASSERT_EQ(tree.Root()->Height(), 2);
    ASSERT_EQ(tree.Root()->Value(), 2);

    auto tree2 = Tree::AVL<int, int>();
    tree2.Insert({10, 1});
    tree2.Insert({5, 3});
    tree2.Insert({8, 4});
    ASSERT_EQ(tree2.Root()->Key(), 8);
    ASSERT_EQ(tree2.Root()->Height(), 2);
    ASSERT_EQ(tree2.Root()->Value(), 4);

    auto tree3 = Tree::AVL<int, int>();
    tree3.Insert({5, 1});
    tree3.Insert({10, 3});
    tree3.Insert({8, 2});
    ASSERT_FALSE(tree3.Insert({8, 3}));
    ASSERT_EQ(tree3.Root()->Key(), 8);
    ASSERT_EQ(tree3.Root()->Height(), 2);

    auto tree4 = Tree::AVL<int, int>();
    tree4.Insert({10, 1});
    tree4.Insert({6, 3});
    tree4.Insert({12, 2});
    tree4.Insert({16, 2});
    tree4.Insert({14, 5});
    ASSERT_EQ(tree4.Root()->Key(), 10);
    ASSERT_EQ(tree4.Root()->Height(), 3);
}

TEST(AVLTest, FindNode) {
    auto tree3 = Tree::AVL<int, int>();
    tree3.Insert({5, 1});
    tree3.Insert({10, 3});
    tree3.Insert({8, 2});
    ASSERT_EQ(tree3.Root()->Key(), 8);
    ASSERT_EQ(tree3.Root()->Height(), 2);
    ASSERT_EQ(tree3.Search(10)->Value(), 3);
    ASSERT_EQ(tree3[10].Value(), 3);
    tree3[10] = 4;
    ASSERT_EQ(tree3[10].Value(), 4);

    auto tree4 = Tree::AVL<int, int>{{5, 1}, {10, 1}, {8, 2}};
    tree4.Insert({11, 0});
    tree4.Insert({7, 12});
    tree4.Insert({9, 13});
    tree4.Insert({12, 15});
    tree4.Insert({13, 16});
    ASSERT_EQ(tree4.SearchNearSmallest(14), tree4.Search(13));
    ASSERT_EQ(tree4.SearchNearSmallest(6), tree4.Search(5));
    ASSERT_EQ(tree4.SearchNearSmallest(2), nullptr);
}

TEST(AVLTest, DeleteNode) {
    auto tree = Tree::AVL<int, int>{{5, 1}, {10, 1}, {8, 2}};
    tree.Remove(5);
    ASSERT_EQ(tree.Search(5), nullptr);

    ASSERT_TRUE(tree.Insert({5, 1}));
    ASSERT_TRUE(tree.Insert({4, 1}));
    ASSERT_TRUE(tree.Remove(5));
    ASSERT_EQ(tree.Search(5), nullptr);
    ASSERT_EQ(tree.Root()->Height(), 2);
    ASSERT_FALSE(tree.Remove(5));

    auto tree2 = Tree::AVL<int, int>{{5, 1}, {10, 1}, {8, 2}};
    tree2.Insert({11, 0});
    tree2.Insert({7, 12});
    tree2.Insert({9, 13});

    ASSERT_TRUE(tree2.Remove(8));
    ASSERT_EQ(tree2.Root()->Key(), 9);
    ASSERT_EQ(tree2.Root()->Value(), 13);
    ASSERT_EQ(tree2.Root()->Height(), 3);
    tree2.Remove(11);
    ASSERT_EQ(tree2.Root()->Height(), 3);

    tree2.Remove(10);
    ASSERT_EQ(tree2.Root()->Key(), 7);
    ASSERT_EQ(tree2.Root()->Height(), 2);
    tree2.Remove(7);
    ASSERT_EQ(tree2.Root()->Key(), 9);
    tree2.Remove(9);
    ASSERT_EQ(tree2.Root()->Key(), 5);
    ASSERT_EQ(tree2.Root()->Height(), 1);
    tree2.Remove(5);
    ASSERT_FALSE(tree2.Root());

    auto tree3 = Tree::AVL<int, int>{{5, 1}, {10, 1}, {8, 2}};
    tree3.Insert({11, 0});
    tree3.Insert({7, 12});
    tree3.Insert({9, 13});
    tree3.Insert({12, 15});
    tree3.Insert({13, 16});
    tree3.Remove(10);
    tree3.Remove(7);
    ASSERT_EQ(tree3.Root()->Key(), 11);
    ASSERT_EQ(tree3.Root()->Height(), 3);
}

TEST(AVLTest, ConstructionTest) {
    auto tree = Tree::AVL<int, int>{{5, 1}, {10, 1}, {8, 2}};
    ASSERT_EQ(tree.Root()->Key(), 8);
    ASSERT_EQ(tree.Root()->Height(), 2);
}

TEST(AVLTest, MemoryLeak) {
#if DEBUG
    _CrtMemState memState;
    _CrtMemCheckpoint(&memState);
    {
        _CrtMemState stateNow, stateDiff1;
        auto tree = Tree::AVL<int, int>{{5, 3}, {10, 3}, {8, 1}};
        _CrtMemCheckpoint(&stateNow);
        int diffResult = _CrtMemDifference(&stateDiff1, &memState, &stateNow);

        if (!diffResult) {
            FAIL() << fmt::format("Memory is created {} byte(s)", stateDiff1.lSizes[1]);
        }
    }

    _CrtMemState stateNow2, stateDiff2;
    _CrtMemCheckpoint(&stateNow2);
    int diffResult2 = _CrtMemDifference(&stateDiff2, &memState, &stateNow2);
    if (diffResult2) {
        FAIL() << fmt::format("Memory leak of {} byte(s) detected", stateDiff2.lSizes[1]);
    }
#else
#endif
}
