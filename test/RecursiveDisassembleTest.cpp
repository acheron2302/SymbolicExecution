#include <crtdbg.h>
#include <fmt/format.h>
#include <gtest/gtest.h>

#include "TraversalDisassemble.h"

class RecursiveDisassembleTest : public ::testing::Test {
  protected:
    static disas::RecursiveDisassemble *testDis;

    static void SetUpTestSuite() {
        std::string fileName = "C:\\Users\\Analysis Box\\Desktop\\malware "
                               "collection\\APT\\APT32\\MSVCR100.dll";
        testDis = new disas::RecursiveDisassemble(fileName);
    }

    static void TearDownTestSuite() {
        delete testDis;
        testDis = nullptr;
    }

    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

disas::RecursiveDisassemble *RecursiveDisassembleTest::testDis = nullptr;

TEST_F(RecursiveDisassembleTest, ConstructionTest) {
    testDis->DisassembleFunction();
    auto funcs = testDis->GetVecFunc();
    ASSERT_EQ(funcs.size(), 3);
    ASSERT_EQ(funcs[0x10010465].StartAddress(), 0x10010465);
    ASSERT_EQ(funcs[0x10010465].Size(), 4);
    ASSERT_EQ(funcs[0x10018bc0].StartAddress(), 0x10018bc0);
    ASSERT_EQ(funcs[0x10018bc0].Size(), 1);
    auto block_value = funcs[0x10010465].GetBlockAtStartAddr(0x10010477);
    if (!block_value.has_value()) {
        FAIL() << "Fail to get block at 0x10010465";
    }
    auto block = block_value.value();
    ASSERT_EQ(block->NumberOfInstructions(), 1);

    block_value = funcs[0x10010465].GetBlockAtAddr(0x10010469);
    if (!block_value.has_value()) {
        FAIL() << "Fail to get block at 0x10010469";
    }
    auto block2 = block_value.value();
    ASSERT_EQ(block2->NumberOfInstructions(), 11);

    testDis->DisassembleFunction();
    ASSERT_EQ(funcs[0x10018bc0].Size(), 18);
    block_value = funcs[0x10018bc0].GetBlockAtAddr(0x10018c64);
    if (!block_value.has_value()) {
        FAIL() << "Fail to get block at 0x10018c64";
    }
    auto block3 = block_value.value();
    ASSERT_EQ(block3->GetStartAddress(), 0x10018c5d);
    ASSERT_EQ(block3->NumberOfInstructions(), 4);
}

TEST_F(RecursiveDisassembleTest, LeakTest) {
#if _DEBUG
    std::string fileName2 = "C:\\Users\\Analysis Box\\Desktop\\malware "
                            "collection\\APT\\APT32\\MSVCR100.dll";
    _CrtMemState memState;
    _CrtMemCheckpoint(&memState);
    {
        _CrtMemState stateNow, stateDiff1;
        disas::RecursiveDisassemble testDisas(fileName2);
        testDisas.DisassembleBlock();
        _CrtMemCheckpoint(&stateNow);
        int diffResult = _CrtMemDifference(&stateDiff1, &memState, &stateNow);

        if (!diffResult) {
            FAIL() << fmt::format("Expect create {} byte(s)", stateDiff1.lSizes[1]);
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
