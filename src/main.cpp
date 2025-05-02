#include "../include/CLI/CLI11.hpp"
#include "options.h"
#include <iostream>

int main(int argc, char **argv)
{
    CLI::App app{"CLI in C++"};
    argv = app.ensure_utf8(argv);
    std::string name = "";
    int number = -1;

    app.add_option("-n, --name", name, "Name");
    app.add_option("-o, --oddOrEven", number, "Integer Number");

    CLI11_PARSE(app, argc, argv);

    if(name == "" && number == -1)
    {
        app.exit(CLI::CallForHelp());
    }
    oddOrEven(number);
    greeting(name);
    return 0;
}
