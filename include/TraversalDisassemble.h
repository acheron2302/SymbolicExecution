#pragma once
#include "AVLTree.h"
#include "Block/Block.h"
#include "Block/Function.h"
#include "ReadFileUtil.h"
#include <Zydis/Zydis.h>
#include <queue>
#include <stack>

namespace disas {
#define MAX_DISASSEMBLE_BUFFER 16

struct RecursiveDisassemble {
  private:
    char arr[MAX_DISASSEMBLE_BUFFER];
    std::unique_ptr<file::File> file;
    std::deque<block::shared_block> analysisQueue;
    std::deque<function::shared_function> funcQueue;
    function::VecFunction functionList;
    Tree::AVL<uint64_t, std::weak_ptr<block::InstructionBlock>> doneList;

    ZydisMachineMode mode;
    ZydisStackWidth stackWidth;
    ZydisDecoder decoder;
    block::Instruction decodeInstr;
    ZydisDecoderContext ctx;
    ZydisDisassembledInstruction disInstr;

    static bool IsCall(ZydisDecodedInstruction instr) {
        switch (instr.mnemonic) {
        case ZYDIS_MNEMONIC_CALL:
            return true;
        default:
            return false;
        }
    }

    static bool IsRet(ZydisDecodedInstruction instr) {
        switch (instr.mnemonic) {
        case ZYDIS_MNEMONIC_RET:
            return true;
        default:
            return false;
        }
    }

    static bool IsJMP(ZydisDecodedInstruction instr) {
        switch (instr.mnemonic) {
        case ZYDIS_MNEMONIC_JMP:
            return true;
        }
        return false;
    }

    static bool IsCondJMP(const ZydisDecodedInstruction _instr) {
        switch (_instr.mnemonic) {
        case ZYDIS_MNEMONIC_JB:
        case ZYDIS_MNEMONIC_JBE:
        case ZYDIS_MNEMONIC_JCXZ:
        case ZYDIS_MNEMONIC_JECXZ:
        case ZYDIS_MNEMONIC_JKNZD:
        case ZYDIS_MNEMONIC_JKZD:
        case ZYDIS_MNEMONIC_JL:
        case ZYDIS_MNEMONIC_JLE:
        case ZYDIS_MNEMONIC_JNB:
        case ZYDIS_MNEMONIC_JNBE:
        case ZYDIS_MNEMONIC_JNL:
        case ZYDIS_MNEMONIC_JNLE:
        case ZYDIS_MNEMONIC_JNO:
        case ZYDIS_MNEMONIC_JNP:
        case ZYDIS_MNEMONIC_JNS:
        case ZYDIS_MNEMONIC_JNZ:
        case ZYDIS_MNEMONIC_JO:
        case ZYDIS_MNEMONIC_JP:
        case ZYDIS_MNEMONIC_JRCXZ:
        case ZYDIS_MNEMONIC_JS:
        case ZYDIS_MNEMONIC_JZ:
            return true;
        default:
            return false;
        }
    }

    bool DisassembleInstr(const uint64_t _offset) {
        auto vec = this->file->GetDisassemblePart(_offset);
        std::copy(vec.begin(), vec.end(), this->arr);

        if (!ZYAN_SUCCESS(ZydisDisassembleIntel(mode, _offset, this->arr, MAX_DISASSEMBLE_BUFFER, &this->disInstr))) {
            return false;
        }
        return true;
    }

    bool DecodeInstr(const uint64_t _offset) {
        auto vec = this->file->GetDisassemblePart(_offset);
        std::copy(vec.begin(), vec.end(), this->arr);

        if (!ZYAN_SUCCESS(ZydisDecoderDecodeInstruction(&this->decoder, &this->ctx, this->arr, MAX_DISASSEMBLE_BUFFER, &this->decodeInstr))) {
            return false;
        }

        return true;
    }

  public:
    RecursiveDisassemble(const std::string &fileName);

    RecursiveDisassemble() = default;
    void DisassembleBlock();
    bool DisassembleFunction();
    block::shared_block PopAnalysis();
    function::shared_function PopFunction();

    bool IsDisassembled(uint64_t offset);

    bool PushJmpBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func_block);
    bool PushTrueBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func_block);
    bool PushFalseBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func_block);
    bool PushNextInstr(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func_block);
    bool PushNewCall(ZyanU64 start_offset, block::shared_block instr_block);
    // this function is use to determinate which will be call handle first
    // for VMProtect you want to reverse hook this function and reverse the order
    bool PushCallBlock(ZyanU64 start_offset, block::shared_block instr_block, function::shared_function func);


    function::VecFunction GetVecFunc() {
        return functionList;
    }
};
} // namespace disas