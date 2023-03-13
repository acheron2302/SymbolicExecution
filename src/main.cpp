#include "main.h"
#include <argparse/argparse.hpp>

#include <Windows.h>
#include <inttypes.h>

#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <stack>

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("Nys");
    program.add_argument("--file").required().help("Input a file to analyse");

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    std::string file_name = program.get<std::string>("--file");
    fmt::print("Hello World: {}\n", file_name);
    return 0;
}