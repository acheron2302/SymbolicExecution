#include "Block/Block.h"

block::shared_block block::InstructionBlock::SplitAtAddress(uint64_t addr) {
    uint64_t pos = this->InstrPos(addr);
    auto temp_instr = this->instr[pos];
    auto temp_end = temp_instr.Address();

    std::vector<Instruction> low_part(this->instr.begin(), this->instr.begin() + pos);
    std::vector<Instruction> high_part(this->instr.begin() + pos, this->instr.end());

    this->instr = low_part;
    this->endAddress = temp_end;
   
    auto new_block = block::NewSharedBlock(temp_end, high_part);
    this->numInstr = this->numInstr - new_block->numInstr;
    return new_block;
}

std::shared_ptr<block::Edge> block::InstructionBlock::NewEdge(block::shared_block _outBlock) {
    std::shared_ptr<Edge> newEdge = std::make_shared<Edge>(_outBlock);
    this->outVec.push_back(newEdge);
    _outBlock->inVec.push_back(newEdge);
    return newEdge;
}

std::shared_ptr<block::Edge> block::InstructionBlock::NewEdge(block::shared_block _outBlock, bool _isTrue) {
    std::shared_ptr<Edge> newEdge = std::make_shared<Edge>(_outBlock, _isTrue);
    this->outVec.push_back(newEdge);
    _outBlock->inVec.push_back(newEdge);
    return newEdge;
}

void block::InstructionBlock::AddInstruction(std::vector<Instruction*> _instr) {
    for (auto each_instr : _instr) {
        this->instrAddrMap.emplace(each_instr->Address(), this->numInstr);
        this->numInstr += 1;
        this->instr.push_back(*each_instr);
        this->endAddress += each_instr->length;
    }
}

void block::InstructionBlock::AddInstruction(Instruction *_instr) {
    _instr->Address(this->endAddress);
    this->instrAddrMap.emplace(_instr->Address(), this->numInstr);
    this->instr.push_back(*_instr);
    this->endAddress += _instr->length;

    this->numInstr += 1;
}

void block::InstructionBlock::ShrinkToFitInstruction() {
    /// <summary>
    /// Shrink the instruction so the vector doesn't take too much size
    /// </summary>
    this->instr.shrink_to_fit();
}

block::shared_block block::NewSharedBlock(uint64_t _offset) {
    return std::make_shared<block::InstructionBlock>(_offset);
}

block::shared_block block::NewSharedBlock(uint64_t _offset, std::vector<Instruction> _instr) {
    return std::make_shared<block::InstructionBlock>(_offset, _instr);
}

bool block::BFSIterator::operator==(const block::BFSIterator &rhs) {
    if ((rhs.blockPtr == nullptr && this == nullptr) || (this != nullptr && rhs.blockPtr == nullptr)) {
        return false;
    } else if ((rhs.blockPtr == nullptr && this != nullptr) || (rhs.blockPtr != nullptr && this == nullptr)) {
        return true;
    }
    return this->blockPtr->GetStartAddress() == rhs.blockPtr->GetStartAddress();
}

bool block::BFSIterator::operator!=(const block::BFSIterator &rhs) {
    if ((rhs.blockPtr == nullptr && this->blockPtr != nullptr) || (rhs.blockPtr != nullptr && this->blockPtr == nullptr)) {
        return true;
    } else if ((rhs.blockPtr == nullptr && this->blockPtr == nullptr) || (this->blockPtr != nullptr && rhs.blockPtr == nullptr)) {
        return false;
    }
    return this->blockPtr->GetStartAddress() != rhs.blockPtr->GetStartAddress();
}