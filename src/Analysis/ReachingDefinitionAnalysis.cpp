#include "Analysis/ReachingDefinitionAnalysis.h"

void rda::BlockRDA::LiftBlock(block::shared_block _block) {
    uint64_t size = _block->GetBlockSize();
    uint64_t start_addr = _block->GetStartAddress();
    std::vector<uint8_t> binary_block = this->file.GetPartOfFile(start_addr, size);

}
