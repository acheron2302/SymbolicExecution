#pragma once
#include "AVLTree.h"
#include "Block.h"
#include <vector>

namespace function {
class FunctionRead {
  public:
    virtual std::optional<block::shared_block> GetBlockAtStartAddr(uint64_t _startAddr) = 0;
    virtual std::optional<block::shared_block> GetBlockAtAddr(uint64_t _addr) = 0;
    virtual block::shared_block GetBeginBlock() = 0;
    virtual block::BFSIterator begin() = 0;
    virtual block::BFSIterator end() = 0;
};

class Function : public FunctionRead {
  private:
    Tree::AVL<uint64_t, block::shared_block> functionBlock;
    uint64_t blockNum;
    uint64_t startAddress;

  public:
    Function(uint64_t _startAddress) : startAddress(_startAddress), blockNum(0) {
    }
    Function(block::shared_block _block) {
        this->blockNum = 0;
        this->startAddress = _block->GetStartAddress();
        AddNewBlock(_block);
    }
    bool AddNewBlock(block::shared_block block);
    bool AddNewEdge(block::shared_block src, block::shared_block dest);
    bool AddNewEdge(block::shared_block src, block::shared_block dest, bool _isTrue);
    std::optional<block::shared_block> GetBlockAtStartAddr(uint64_t _startAddr);
    std::optional<block::shared_block> GetBlockAtAddr(uint64_t _addr);
    block::shared_block GetBeginBlock();
    block::BFSIterator begin();
    block::BFSIterator end();
    uint64_t StartAddress() {
        return startAddress;
    }
    uint64_t Size() {
        return blockNum;
    }
};

class VecFunction : public std::vector<std::shared_ptr<function::Function>> {
  public:
    function::Function &operator[](uint64_t _startAddress);
};

typedef std::shared_ptr<Function> shared_function;
} // namespace function
