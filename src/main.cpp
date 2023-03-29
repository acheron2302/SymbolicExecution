#include "main.h"
extern "C" {
    #include <pyvex.h>
    #include <libvex.h>
}
#include <argparse/argparse.hpp>
#include <Windows.h>
#include <inttypes.h>

#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <stack>

#pragma comment(lib, "pyvex.lib")

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("Nys");
    program.add_argument("--file")
        .required()
        .help("Input a file to analyse");

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    std::string file_name = program.get<std::string>("--file");
    fmt::print("Hello World: {}\n", file_name);
    auto result = file::NewFile(file_name);
    if (result.has_value()) {
        fmt::print("[!] Error: file is not PE or doesn't exist");
    }

    if (!result.has_value()) {
        fmt::print("Cannot find pe file: {}", file_name);
        return -1;
    }
    return 0;
}