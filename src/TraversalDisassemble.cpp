#include "TraversalDisassemble.h"

using namespace disas;

RecursiveDisassemble::RecursiveDisassemble(const std::string &fileName) {
    file = std::move(std::make_unique<file::File>(fileName));

    // Create new function and block
    auto nextBlock = std::make_shared<block::InstructionBlock>(file->GetEntryPointVA());
    analysisQueue.push_front(nextBlock);
    auto func = std::make_shared<function::Function>(nextBlock);
    functionList.push_back(func);
    this->funcQueue.push_front(func);
    this->doneList[file->GetEntryPointVA()] = nextBlock;

    if (file->GetArch() == file::ARCH32BIT) {
        this->mode = ZYDIS_MACHINE_MODE_LONG_COMPAT_32;
        this->stackWidth = ZYDIS_STACK_WIDTH_32;
    } else {
        this->mode = ZYDIS_MACHINE_MODE_LONG_64;
        this->stackWidth = ZYDIS_STACK_WIDTH_64;
    }
    ZydisDecoderInit(&this->decoder, this->mode, this->stackWidth);
}

bool RecursiveDisassemble::IsDisassembled(uint64_t offset) {
    auto foundBlock = doneList.SearchNearSmallest(offset);
    if (foundBlock == nullptr) {
        return false;
    }
    auto block = foundBlock->Value();
    if (block.expired()) {
        return false;
    }
    auto shared_block = block.lock();
    if (shared_block->GetStartAddress() == offset) {
        return true;
    }
    if (shared_block != nullptr && offset < shared_block->GetBlockSize() + shared_block->GetStartAddress()) {
        return true;
    }
    return false;
}

bool RecursiveDisassemble::DisassembleFunction() {
    /// <summary>
    /// Disassemble a function which is on the stack
    /// </summary>
    /// <returns>
    /// return true if it can disassemble the function and false otherwise
    /// </returns>
    while (!this->analysisQueue.empty()) {
        DisassembleBlock();

        // if we find that the address of the block analysis equal to the beginning
        // of the function then we stop the analysis because that's another function
        // block
        if (this->analysisQueue.empty()) {
            return true;
        }

        // The analysis Queue is equal to function queue so we end because that's a mark of new function
        if (this->analysisQueue.front()->GetStartAddress() == this->funcQueue.front()->StartAddress()) {
            return true;
        }
    }
    return true;
}

void RecursiveDisassemble::DisassembleBlock() {
    /// <summary>
    /// Dissasemble a block which was push into queue
    /// Doesn't do anything if the queue is empty
    /// For the call function it will push the address of next instruction first
    /// and then the call instruction This process can be hook to make reverse
    /// </summary>

    if (this->analysisQueue.empty()) {
        return;
    }

    const block::shared_block instr_block = this->PopAnalysis();
    auto func = PopFunction();
    ZyanU64 start_offset = instr_block->GetStartAddress();

    // Loop to decode each instruction
    while (true) {
        // Check if the instruction is in part of another basic block
        if (this->doneList.Search(start_offset) != nullptr && start_offset != instr_block->GetStartAddress()) {
            auto found = this->doneList.Search(start_offset)->Value();
            auto next_block = found.lock();
            func->AddNewEdge(instr_block, next_block);
            return;
        }
        this->DecodeInstr(start_offset);
        instr_block->AddInstruction(&this->decodeInstr);

        // Check if it is call instruction
        if (IsCall(this->decodeInstr)) {
            PushCallBlock(start_offset, instr_block, func);
            return;
        }

        if (IsCondJMP(this->decodeInstr)) {
            PushTrueBlock(start_offset, instr_block, func);
            PushFalseBlock(start_offset, instr_block, func);
            return;
        }

        if (IsJMP(this->decodeInstr)) {
            PushJmpBlock(start_offset, instr_block, func);
            return;
        }

        if (IsRet(this->decodeInstr)) {
            return;
        }

        // Check if it is a jmp instruction
        start_offset += this->decodeInstr.length;
    }

    // Shrink it because we won't add anymore instruction
    instr_block->ShrinkToFitInstruction();
}

bool RecursiveDisassemble::PushJmpBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func_block) {
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT_VISIBLE];
    if (!ZYAN_SUCCESS(ZydisDecoderDecodeOperands(&this->decoder, &this->ctx, &this->decodeInstr, operands, ZYDIS_MAX_OPERAND_COUNT_VISIBLE))) {
        return false;
    }
    ZyanU64 next_instr_addr = start_offset + this->decodeInstr.length;
    block::shared_block newBlock = block::NewSharedBlock(next_instr_addr + operands[0].imm.value.s);
    this->doneList[next_instr_addr + operands[0].imm.value.s] = newBlock;
    func_block->AddNewEdge(instr_block, newBlock);
    if (!func_block->GetBlockAtStartAddr(newBlock->GetStartAddress()).has_value()) {
        func_block->AddNewBlock(newBlock);
    }

    this->funcQueue.push_front(func_block);
    this->analysisQueue.push_front(newBlock);
    return true;
}

bool RecursiveDisassemble::PushTrueBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func_block) {
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT_VISIBLE];
    if (!ZYAN_SUCCESS(ZydisDecoderDecodeOperands(&this->decoder, &this->ctx, &this->decodeInstr, operands, ZYDIS_MAX_OPERAND_COUNT_VISIBLE))) {
        return false;
    }

    ZyanU64 next_instr_addr = start_offset + this->decodeInstr.length;
    ZyanU64 next_addr = next_instr_addr + operands[0].imm.value.s;
    if (IsDisassembled(next_addr)) {
        return true;
    }
    block::shared_block newBlock = block::NewSharedBlock(next_instr_addr + operands[0].imm.value.s);
    this->doneList[next_addr] = newBlock;
    func_block->AddNewEdge(instr_block, newBlock, true);
    if (!func_block->GetBlockAtStartAddr(newBlock->GetStartAddress()).has_value()) {
        func_block->AddNewBlock(newBlock);
    }

    this->funcQueue.push_front(func_block);
    this->analysisQueue.push_front(newBlock);
    return true;
}

bool RecursiveDisassemble::PushFalseBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func_block) {
    ZyanU64 next_instr_addr = start_offset + this->decodeInstr.length;
    if (IsDisassembled(next_instr_addr)) {
        return true;
    }

    auto new_block = block::NewSharedBlock(next_instr_addr);
    this->doneList[next_instr_addr] = new_block;
    func_block->AddNewEdge(instr_block, new_block, false);
    if (!func_block->GetBlockAtStartAddr(new_block->GetStartAddress()).has_value()) {
        func_block->AddNewBlock(new_block);
    }

    // Add to queue for next analysis
    this->analysisQueue.push_front(new_block);
    this->funcQueue.push_front(func_block);
    return true;
}

block::shared_block RecursiveDisassemble::PopAnalysis() {
    auto result = this->analysisQueue.front();
    this->analysisQueue.pop_front();
    return result;
}

function::shared_function RecursiveDisassemble::PopFunction() {
    auto result = this->funcQueue.front();
    this->funcQueue.pop_front();
    return result;
}

bool RecursiveDisassemble::PushNextInstr(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func) {
    ZyanU64 next_instr_addr = start_offset + this->decodeInstr.length;
    if (IsDisassembled(next_instr_addr)) {
        return true;
    }

    auto new_block = block::NewSharedBlock(next_instr_addr);
    this->doneList[next_instr_addr] = new_block;
    func->AddNewEdge(instr_block, new_block);
    if (!func->GetBlockAtStartAddr(new_block->GetStartAddress()).has_value()) {
        func->AddNewBlock(new_block);
    }

    // Add to queue for next analysis
    this->analysisQueue.push_front(new_block);
    this->funcQueue.push_front(func);
    return true;
}

bool RecursiveDisassemble::PushNewCall(ZyanU64 start_offset, block::shared_block instr_block) {
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT_VISIBLE];
    if (!ZYAN_SUCCESS(ZydisDecoderDecodeOperands(&this->decoder, &this->ctx, &this->decodeInstr, operands, ZYDIS_MAX_OPERAND_COUNT_VISIBLE))) {
        return false;
    }

    ZyanU64 next_instr_addr = start_offset + this->decodeInstr.length + operands[0].imm.value.s;
    // check if the next call block has been pushed to the stack
    if (IsDisassembled(next_instr_addr)) {
        return true;
    }

    block::shared_block newFunctionBlock = block::NewSharedBlock(next_instr_addr);
    function::shared_function newFunction = std::make_shared<function::Function>(newFunctionBlock);
    this->doneList[next_instr_addr] = newFunctionBlock;

    this->functionList.push_back(newFunction);
    this->funcQueue.push_back(newFunction);
    this->analysisQueue.push_back(newFunctionBlock);
    return true;
}

bool RecursiveDisassemble::PushCallBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func) {
    // Add the next instruction to the queue
    this->PushNextInstr(start_offset, instr_block, func);

    // Add the call address to the queue
    this->PushNewCall(start_offset, instr_block);
    return true;
}