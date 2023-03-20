#include "ReadFileUtil.h"

std::optional<file::File*> file::NewFile(std::string name) {
    auto pe_file = new file::File(name);
    if (pe_file->IsNullPtr()) {
        return std::nullopt;
    }
    return pe_file;
}