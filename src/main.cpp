#include "../include/CLI/CLI11.hpp"
#include <iostream>

int main(int argc, char** argv) {
    CLI::App app{"CLI in C++"};
    std::string name = "Welt";
    app.add_option("-n,--name", name, "Name");

    CLI11_PARSE(app, argc, argv);

    std::cout << "Hallo, " << name << "!" << std::endl;
    return 0;
}
