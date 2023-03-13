#pragma once

#include "Block/Block.h"
#include "Block/Function.h"
#include "error/Error.h"

#include <fmt/format.h>
#include <list>
#include <memory>
namespace analyse {
class Dominator;
class DominatorTree;
class DominatorNode {
    friend DominatorTree;

  private:
    block::shared_block curr = nullptr;
    std::list<DominatorNode *> treeChildren;

  public:
    DominatorNode(block::shared_block _childBlock) noexcept {
        curr = _childBlock;
    }

    DominatorNode(DominatorNode &&newNode) noexcept : curr(std::move(newNode.curr)), treeChildren(std::move(newNode.treeChildren)) {
    }

    std::list<DominatorNode *> &Children() {
        return treeChildren;
    }
    block::shared_block &Value() {
        return curr;
    }

    ~DominatorNode() {
        for (auto eachChild : treeChildren) {
            delete eachChild;
        }
    }
};

class DominatorTree {

  private:
    block::shared_block root;
    std::list<DominatorNode *> node;

  public:
    DominatorTree(Dominator &_dominator);
    ~DominatorTree() {
        for (auto eachChild : node) {
            delete eachChild;
        }
    }
    block::shared_block &Value() {
        return root;
    }
    std::list<DominatorNode *> &Children() {
        return node;
    }
};

class Dominator {
    /// <summary>
    /// The Dominator tree get store inside doms doms map. Because every block only has one IDOM, so we can map
    /// each block to its IDOM and for every block b in graph DOM(b) = {b} union IDOM(b) union IDOM(IDOM(b)) union ...
    /// So we can build the dominator tree from every edge.
    /// </summary>

    friend DominatorTree;

  private:
    std::unordered_map<block::shared_block, block::shared_block> doms;
    std::unordered_map<block::shared_block, uint64_t> blockNum;
    block::shared_block root;
    function::FunctionRead &func;
    std::unordered_map<uint64_t, std::list<block::shared_block>> dominance_frontier;

    std::optional<std::unordered_map<block::shared_block, uint64_t>> PostOrderEnumerate(function::FunctionRead &func);
    block::shared_block Intersect(block::shared_block b1, block::shared_block b2);
    void InitDominanceFrotier();

  public:
    inline std::unordered_map<block::shared_block, block::shared_block> DomsMaps() {
        return doms;
    }
    inline std::unordered_map<uint64_t, std::list<block::shared_block>> DomianceFrontier() {
        return dominance_frontier;
    }
    DominatorTree GetDominatorTree();
    Dominator(function::FunctionRead &_func);
    Dominator() = default;
    ~Dominator() {
    }
};

class DominatorTreeRead {
    virtual block::shared_block &Value() = 0;
    virtual std::list<std::unique_ptr<DominatorNode>> &Children() = 0;
};
} // namespace analyse