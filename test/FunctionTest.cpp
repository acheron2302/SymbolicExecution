#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "Block/Block.h"
#include "Block/Dominator.h"
#include "Block/Function.h"

class TestFunction : public ::testing::Test {
  protected:
    static function::shared_function testFunc;

    static void SetUpTestSuite() {
        block::shared_block block1 = std::make_shared<block::InstructionBlock>(0x1);
        block::shared_block block2 = std::make_shared<block::InstructionBlock>(0x2);
        block::shared_block block3 = std::make_shared<block::InstructionBlock>(0x3);
        block::shared_block block4 = std::make_shared<block::InstructionBlock>(0x4);
        block::shared_block block5 = std::make_shared<block::InstructionBlock>(0x5);
        block::shared_block block6 = std::make_shared<block::InstructionBlock>(0x6);
        block::shared_block block7 = std::make_shared<block::InstructionBlock>(0x7);

        testFunc = std::make_shared<function::Function>(block1);
        testFunc->AddNewBlock(block2);
        testFunc->AddNewBlock(block3);
        testFunc->AddNewBlock(block4);
        testFunc->AddNewBlock(block5);
        testFunc->AddNewBlock(block6);
        testFunc->AddNewBlock(block7);
        testFunc->AddNewEdge(block1, block2);
        testFunc->AddNewEdge(block2, block3);
        testFunc->AddNewEdge(block2, block4);
        testFunc->AddNewEdge(block3, block5);
        testFunc->AddNewEdge(block4, block5);
        testFunc->AddNewEdge(block5, block6);
        testFunc->AddNewEdge(block5, block7);
        testFunc->AddNewEdge(block7, block2);
    }

    static void TearDownTestSuite() {
    }

    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

function::shared_function TestFunction::testFunc = nullptr;

TEST_F(TestFunction, ConstructionAndInsert) {
    block::shared_block block1 = std::make_shared<block::InstructionBlock>(0x1);
    block::shared_block block2 = std::make_shared<block::InstructionBlock>(0x2);
    block::shared_block block3 = std::make_shared<block::InstructionBlock>(0x3);
    function::shared_function testFunc1 = std::make_shared<function::Function>(block1);
    testFunc1->AddNewBlock(block2);
    testFunc1->AddNewEdge(block1, block2);
    function::shared_function testFunc2 = std::make_shared<function::Function>(block2);
    function::shared_function testFunc3 = std::make_shared<function::Function>(block3);
    function::VecFunction vecFunc;
    vecFunc.push_back(testFunc1);
    vecFunc.push_back(testFunc2);
    vecFunc.push_back(testFunc3);
    ASSERT_EQ(vecFunc[0x1].StartAddress(), 0x1);
    ASSERT_EQ(vecFunc[0x2].StartAddress(), 0x2);

    function::FunctionRead &funcRead1 = *testFunc.get();
    uint64_t counter = 0;
    for (auto eachBlock : funcRead1) {
        auto result = eachBlock->GetStartAddress();
        EXPECT_TRUE(result == 0x1 || result == 0x2 || result == 0x3 || result == 0x4 || result == 0x5 || result == 0x6 || result == 0x7);
        ASSERT_THAT(counter, ::testing::Lt(7));
    }
}

TEST_F(TestFunction, DominatorTest) {
    auto dom = analyse::Dominator::Dominator(*testFunc.get());
    auto domTree = dom.GetDominatorTree();
    ASSERT_EQ(domTree.Value(), testFunc->GetBeginBlock());
    auto block = domTree.Children().front()->Children();
    for (auto eachBlock : block) {
        auto value = eachBlock->Value()->GetStartAddress();
        EXPECT_TRUE(value == 0x3 || value == 0x4 || value == 0x5);
    }

    auto dominance_frontier = dom.DomianceFrontier();
    ASSERT_EQ(dominance_frontier[0x2].size(), 1);
    ASSERT_EQ(dominance_frontier[0x3].size(), 0);
}