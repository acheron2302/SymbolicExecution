#pragma once
#include "error/Error.h"

#include <Zydis/Zydis.h>
#include <deque>
#include <functional>
#include <memory>
#include <queue>
#include <set>
#include <map>

namespace block {
class InstructionBlock;
class Edge {
    bool isConditionEdge;
    bool isTrue;
    std::weak_ptr<InstructionBlock> outBlock;
    std::weak_ptr<InstructionBlock> srcBlock;
    friend class InstructionBlock;

  public:
    Edge() = default;

    Edge(std::shared_ptr<InstructionBlock> _outBlock) : isConditionEdge(false), isTrue(false) {
        this->outBlock = _outBlock;
    }

    Edge(std::shared_ptr<InstructionBlock> _outBlock, bool _isTrue) : isTrue(_isTrue), isConditionEdge(true) {
        this->outBlock = _outBlock;
    }

    bool IsCondition() {
        return isConditionEdge;
    }

    bool IsTrue() {
        return isTrue;
    }

    Edge *SrcBlock(std::shared_ptr<InstructionBlock> _block) {
        this->srcBlock = _block;
        return this;
    }

    Edge *OutBlock(std::shared_ptr<InstructionBlock> _block) {
        this->outBlock = _block;
        return this;
    }

    bool SwitchCond() {
        this->isConditionEdge = !this->isConditionEdge;
        return this->isConditionEdge;
    }

    bool SetCond(bool _isTrue) {
        if (this->isConditionEdge) {
            this->isTrue = _isTrue;
            return true;
        }
        return false;
    }

    std::shared_ptr<InstructionBlock> SrcBlock() {
        if (this->srcBlock.expired()) {
            return nullptr;
        }
        return this->srcBlock.lock();
    }

    std::shared_ptr<InstructionBlock> OutBlock() {
        if (this->outBlock.expired()) {
            return nullptr;
        }
        return this->outBlock.lock();
    }
};

class Instruction : public ZydisDecodedInstruction {
    uint64_t address;

  public:
    inline uint64_t Address() noexcept {
        return address;
    }
    inline void Address(uint64_t _addr) noexcept {
        this->address = _addr;
    }
};

class InstructionBlock {
  private:
    std::vector<Instruction> instr;
    std::list<std::shared_ptr<Edge>> outVec;
    std::list<std::shared_ptr<Edge>> inVec;
    uint64_t startAddress;
    uint64_t endAddress;
    uint64_t numInstr = 0;

    std::map<uint64_t, uint64_t> instrAddrMap; // A balance tree to find address to the location of the instruction
                                               // We want to use red black tree instead because it is faster to insert and we don't look
                                               // up many times

  public:
    InstructionBlock() = default;
    InstructionBlock(uint64_t _startAddress, std::vector<Instruction> _instr) : instr(_instr), startAddress(_startAddress), numInstr(0) {
        endAddress = _startAddress;
        for (auto& each_instr : _instr) {
            endAddress += each_instr.length;
            numInstr += 1;
        }
    }
    InstructionBlock(uint64_t _startAddress) : startAddress(_startAddress), endAddress(_startAddress), numInstr(0) {
    }

    inline uint64_t GetStartAddress() const {
        return startAddress;
    }
    inline uint64_t GetEndAddress() const {
        return endAddress;
    }

    inline uint64_t GetBlockSize() const {
        return endAddress - startAddress;
    }

    inline std::list<std::shared_ptr<Edge>> GetOutVec() {
        return outVec;
    }

    inline std::list<std::shared_ptr<Edge>> GetInVec() {
        return inVec;
    }

    inline uint64_t NumberOfInstructions() {
        return numInstr;
    }

    inline bool operator==(const InstructionBlock &rhs) const {
        return this->startAddress == rhs.startAddress && this->endAddress == rhs.endAddress;
    }

    std::shared_ptr<block::Edge> NewEdge(std::shared_ptr<InstructionBlock> _outBlock);
    std::shared_ptr<block::Edge> NewEdge(std::shared_ptr<InstructionBlock> _outBlock, bool _isTrue);

    std::shared_ptr<InstructionBlock> SplitAtAddress(uint64_t addr);
    inline uint64_t InstrPos(uint64_t _addr) {
        return this->instrAddrMap[_addr];
    }

    void AddInstruction(std::vector<Instruction *> _instr);
    void AddInstruction(Instruction *_instr);
    void ShrinkToFitInstruction();
};

typedef std::unique_ptr<InstructionBlock> unique_block;
typedef std::shared_ptr<InstructionBlock> shared_block;
typedef std::weak_ptr<InstructionBlock> weak_block;

class BFSIterator {
    friend class InstructionBlock;

  private:
    block::shared_block blockPtr = nullptr;
    std::queue<block::shared_block> blockQueue;
    std::set<block::shared_block> doneList;

  public:
    BFSIterator(block::shared_block _head) {
        if (_head == nullptr) {
            blockPtr = nullptr;
            return;
        }
        blockPtr = _head;
        blockQueue.push(_head);
    }

    BFSIterator &operator++() {
        if (blockQueue.empty()) {
            const auto null_bfs = BFSIterator(nullptr);
            *this = null_bfs;
            return (*this);
        }
        block::shared_block block = blockQueue.front();
        blockQueue.pop();
        blockPtr = block;

        for (auto eachVec : block->GetOutVec()) {
            if (doneList.find(eachVec->OutBlock()) != doneList.end()) {
                continue;
            }
            doneList.insert(eachVec->OutBlock());
            blockQueue.push(eachVec->OutBlock());
        }
        return *this;
    }

    BFSIterator operator++(int) {
        BFSIterator temp{*this};
        ++(*this);

        return temp;
    }

    block::shared_block operator*() {
        return blockPtr;
    }

    block::shared_block &operator->() {
        return blockPtr;
    }
    bool operator==(const BFSIterator &rhs);
    bool operator!=(const BFSIterator &rhs);
};

class EdgeReader {
  public:
    virtual bool IsCondition() = 0;
    virtual bool IsTrue() = 0;
    virtual block::shared_block SrcBlock() = 0;
    virtual block::shared_block OutBlock() = 0;
};

class EdgeWriter {
  public:
    virtual Edge SrcBlock(std::shared_ptr<InstructionBlock> _block) = 0;
    virtual Edge OutBlock(std::shared_ptr<InstructionBlock> _block) = 0;
    virtual bool SwitchCondition() = 0;
    virtual bool SetCond(bool _isTrue) = 0;
};

class BlockReader {
  public:
    virtual uint64_t GetStartAddress() = 0;
    virtual uint64_t GetEndAddress() = 0;
    virtual uint64_t GetBlockSize() = 0;
    virtual std::deque<std::shared_ptr<Edge>> GetOutVec() = 0;
    virtual std::deque<std::shared_ptr<Edge>> GetInVec() = 0;
};

shared_block NewSharedBlock(uint64_t _offset);
shared_block NewSharedBlock(uint64_t _offset, std::vector<Instruction> _instr);
} // namespace block

// Taken from: https://stackoverflow.com/questions/19195183/how-to-properly-hash-the-custom-struct
template <class T>
inline void hash_combine(std::size_t &s, const T &v) {
    std::hash<T> h;
    s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
}

template <>
struct std::hash<block::InstructionBlock> {
    std::size_t operator()(const block::InstructionBlock &block) const noexcept {
        std::size_t res = 0;
        std::size_t h1 = std::hash<uint64_t>{}(block.GetStartAddress());
        std::size_t h2 = std::hash<uint64_t>{}(block.GetEndAddress());
        hash_combine(res, h2);
        hash_combine(res, h1);
        return res;
    }
};
