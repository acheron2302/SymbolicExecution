#ifndef __READFILEUTIL_H_
#define __READFILEUTIL_H_

#pragma once

#include <LIEF/LIEF.hpp>
#include <fmt/format.h>
#include <fstream>
#include <memory>
#include <optional>

namespace file {
enum arch { ARCH32BIT, ARCH64BIT };

struct File {
  private:
    std::unique_ptr<LIEF::PE::Binary> pe;
    std::fstream ifs;
    size_t size;

  public:
    File(const std::string &name) {
        std::fstream fs{name, std::fstream::in | std::fstream::binary};
        ifs = std::move(fs);

        // Get file size
        ifs.seekg(std::fstream::beg);
        auto beg = ifs.tellg();
        ifs.seekg(0, std::fstream::end);
        auto end = ifs.tellg();
        size = end - beg;
        ifs.seekg(std::fstream::beg);

        try {
            this->pe = std::move(LIEF::PE::Parser::parse(name));
            return;
        } catch (std::exception &e) {
            this->pe = nullptr;
            return;
        }
    };

    const size_t Size() { return size; }

    ~File() { ifs.close(); }

    const bool IsNullPtr() {
        if (this->pe == nullptr) {
            return true;
        }
        return false;
    }

    const uint64_t GetEntryPointReal() {
        return pe->va_to_offset(pe->entrypoint());
    }

    const uint64_t GetEntryPointVA() { return pe->entrypoint(); }

    std::vector<uint8_t> GetPartOfFile(uint64_t _vOffset, uint64_t _size) {
        return pe->get_content_from_virtual_address(_vOffset, _size,
                                                    LIEF::Binary::VA_TYPES::VA);
    }

    std::unique_ptr<const char[]> GetFullFile() {
        std::unique_ptr<char[]> content = std::make_unique<char[]>(size);
        ifs.read(content.get(), size);
        return std::move(content);
    }

    std::vector<uint8_t> GetDisassemblePart(uint64_t virtualOffset) {
        return pe->get_content_from_virtual_address(virtualOffset, 16,
                                                    LIEF::Binary::VA_TYPES::VA);
    }

    arch GetArch() {
        if (pe->type() == LIEF::PE::PE_TYPE::PE32) {
            return ARCH32BIT;
        }
        return ARCH64BIT;
    }
};

std::optional<File *> NewFile(std::string name);

} // namespace file

#endif // !__READFILEUTIL_H_