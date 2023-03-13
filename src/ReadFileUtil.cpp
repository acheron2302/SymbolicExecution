#include "ReadFileUtil.h"

file::File *file::NewFile(std::string name) {
    return new file::File(name);
}