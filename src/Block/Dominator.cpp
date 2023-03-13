#include "Block/Dominator.h"

#include <map>
#include <set>
#include <unordered_map>

std::optional<std::unordered_map<block::shared_block, uint64_t>> analyse::Dominator::PostOrderEnumerate(function::FunctionRead &_func) {
    std::stack<block::shared_block> stack;
    std::set<uint64_t> doneList;
    std::unordered_map<block::shared_block, uint64_t> blockNum;

    uint64_t num = 1;
    auto head = _func.GetBeginBlock();
    this->root = head;

    stack.push(head);
    while (!stack.empty()) {
        block::shared_block block = stack.top();
        if (doneList.find(block->GetStartAddress()) != doneList.end()) {
            stack.pop();
            blockNum[block] = num;
            num += 1;
            continue;
        }

        auto outVec = block->GetOutVec();
        for (auto eachVec : outVec) {
            if (doneList.find(eachVec->OutBlock()->GetStartAddress()) != doneList.end()) {
                continue;
            }
            stack.push(eachVec->OutBlock());
        }

        doneList.insert(block->GetStartAddress());
    }

    return blockNum;
}

block::shared_block analyse::Dominator::Intersect(block::shared_block b1, block::shared_block b2) {
    auto finger1 = this->blockNum[b1];
    auto finger2 = this->blockNum[b2];

    while (finger1 != finger2) {
        while (finger1 < finger2) {
            b1 = this->doms[b1];
            finger1 = this->blockNum[b1];
        }
        while (finger2 < finger1) {
            b2 = this->doms[b2];
            finger2 = this->blockNum[b2];
        }
    }
    return b1;
}

analyse::DominatorTree::DominatorTree(Dominator &_dominator) {
    std::map<block::shared_block, DominatorNode *> tmpSet;
    for (auto eachBlock : _dominator.doms) {
        if (eachBlock.first == eachBlock.second) {
            this->root = eachBlock.first;
            continue;
        }

        if (tmpSet.find(eachBlock.first) == tmpSet.end()) {
            tmpSet[eachBlock.first] = new DominatorNode(eachBlock.first);
        }

        if (tmpSet.find(eachBlock.second) == tmpSet.end()) {
            tmpSet[eachBlock.second] = new DominatorNode(eachBlock.second);
        }

        tmpSet[eachBlock.second]->treeChildren.push_back(tmpSet[eachBlock.first]);
    }

    this->node = std::move(tmpSet[this->root]->treeChildren);
}

analyse::DominatorTree analyse::Dominator::GetDominatorTree() {
    return analyse::DominatorTree(*this);
}

void analyse::Dominator::InitDominanceFrotier() {
    for (auto each_block : this->func) {
        auto block_start_addr = each_block->GetStartAddress();
        auto in_vec = each_block->GetInVec();
        if (in_vec.size() < 2) {
            this->dominance_frontier[block_start_addr] = {};
            continue;
        }

        for (auto each_edge : in_vec) {
            auto in_block = each_edge->SrcBlock();
            if (this->doms[each_block] == in_block) {
                continue;
            }
            this->dominance_frontier[block_start_addr].push_back(in_block);
        }

        if (dominance_frontier.find(block_start_addr) == dominance_frontier.end()) {
            this->dominance_frontier[block_start_addr] = {};
        }
    }
}

analyse::Dominator::Dominator(function::FunctionRead &_func) : func(_func) {
    // the function implement from this paper: https://www.cs.rice.edu/~keith/EMBED/dom.pdf
    // Post order number
    auto err = PostOrderEnumerate(_func);
    if (!err.has_value()) {
        throw std::exception("Error when try to enumerate post order");
    }

    blockNum = err.value();
    // Start doing the optimise algorithm
    block::shared_block beginBlock = func.GetBeginBlock();
    doms[beginBlock] = beginBlock;
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto eachBlock : _func) {
            if (eachBlock == beginBlock) {
                continue;
            }

            auto predEdge = eachBlock->GetInVec();
            if (predEdge.empty()) {
                continue;
            }

            auto newIdom = predEdge.front()->SrcBlock();
            predEdge.pop_front();

            for (auto otherEdge : predEdge) {
                auto p = otherEdge->SrcBlock();
                if (doms.find(p) != doms.end()) {
                    newIdom = Intersect(p, newIdom);
                }
            }

            if (this->doms[eachBlock] != newIdom) {
                this->doms[eachBlock] = newIdom;
                changed = true;
            }
        }
    }

    this->InitDominanceFrotier();
}