#include <Block/Block.h>
#include <Block/Dominator.h>
#include <Block/Function.h>
#include <ReadFileUtil.h>

namespace rda {
class BlockRDA {
  private:
    file::File& file;

  public:
    BlockRDA(file::File &_file) : file(_file) {}
    void LiftBlock(block::shared_block _block);
};
} // namespace rda