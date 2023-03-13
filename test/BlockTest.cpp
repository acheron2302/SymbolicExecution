#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "Block/Block.h"
#include "Block/Function.h"

#include <Zydis/Decoder.h>
TEST(BlockTest, TestBlockEdge) {
    block::shared_block block1 = block::NewSharedBlock(0);
    block::shared_block block2 = block::NewSharedBlock(1);
    block::shared_block block3 = block::NewSharedBlock(2);
    auto edge = block1->NewEdge(block2);
    edge->SrcBlock(block1);

    auto edge2 = block1->NewEdge(block3);
    edge2->SrcBlock(block1);

    auto outVecs = block1->GetOutVec();
    ASSERT_THAT(outVecs, ::testing::SizeIs(2));
    ASSERT_THAT(outVecs, ::testing::Contains(edge));
    ASSERT_THAT(outVecs, ::testing::Contains(edge2));
    ASSERT_EQ(edge->OutBlock(), block2);

    block::Instruction decodeInstr;
    ZydisDecoder decoder;
    ZydisDecoderContext ctx;
    char arr[] = "\x90";
    if (!ZYAN_SUCCESS(ZydisDecoderDecodeInstruction(&decoder, &ctx, arr, 4, &decodeInstr))) {
        FAIL() << "Failed to decode";
    }

    block::shared_block block4 = block::NewSharedBlock(3);
    for (int i = 0; i < 10; i++) {
        block4->AddInstruction(&decodeInstr);
    }
    ASSERT_EQ(block4->NumberOfInstructions(), 10);

    auto new_split = block4->SplitAtAddress(8);
    ASSERT_EQ(new_split->GetEndAddress(), 13);
    ASSERT_EQ(new_split->GetStartAddress(), 8);
    ASSERT_EQ(block4->GetEndAddress(), 8);
    ASSERT_EQ(block4->NumberOfInstructions(), 5);
    ASSERT_EQ(new_split->NumberOfInstructions(), 5);
}