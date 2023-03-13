#include "Block/Function.h"

using namespace function;
bool Function::AddNewBlock(block::shared_block block) {
    this->blockNum += 1;
    this->functionBlock[block->GetStartAddress()] = block;
    return true;
}

bool Function::AddNewEdge(block::shared_block src, block::shared_block dest) {
    auto edge = src->NewEdge(dest);
    edge->SrcBlock(src);
    return true;
}

bool Function::AddNewEdge(block::shared_block src, block::shared_block dest, bool _isTrue) {
    auto edge = src->NewEdge(dest, _isTrue);
    edge->SrcBlock(src);
    return true;
}

std::optional<block::shared_block> Function::GetBlockAtStartAddr(uint64_t _startAddr) {
    if (this->functionBlock.Search(_startAddr) == nullptr) {
        return std::nullopt;
    }
    return this->functionBlock[_startAddr].Value();
}

std::optional<block::shared_block> Function::GetBlockAtAddr(uint64_t _addr) {
    if (this->functionBlock.SearchNearSmallest(_addr) == nullptr) {
        return std::nullopt;
    }
    return this->functionBlock.SearchNearSmallest(_addr)->Value();
}

block::shared_block Function::GetBeginBlock() {
    return this->GetBlockAtStartAddr(this->startAddress).value_or(nullptr);
}

block::BFSIterator Function::begin() {
    auto begin = block::BFSIterator::BFSIterator(this->GetBeginBlock());
    begin++;
    return begin;
}

block::BFSIterator Function::end() {
    auto end = block::BFSIterator::BFSIterator(nullptr);
    return end;
}

Function &VecFunction::operator[](uint64_t _startAddress) {
    for (auto eachFunction = this->begin(); eachFunction != this->end(); eachFunction++) {
        if ((*eachFunction)->StartAddress() == _startAddress) {
            return **eachFunction;
        }
    }
    Function func = Function(UINT64_MAX);
    return func;
}
