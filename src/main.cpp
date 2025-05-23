#include "../include/CLI/CLI11.hpp"
#include "options.h"
#include <iostream>

using namespace std;
using namespace CLI;

int main(int argc, char **argv)
{
    App app{"CLI in C++"};
    argv = app.ensure_utf8(argv);
    string name = "";
    int number = 0;
    string gitRepoPath = "";

    app.add_option("-n, --name", name, "Name");
    app.add_option("-o, --oddOrEven", number, "Integer Number");
    app.add_option("-g, --gitxstat", gitRepoPath, "Path to git repo");

    CLI11_PARSE(app, argc, argv);

    if (gitRepoPath != "")
    {
        return gitxstat(gitRepoPath);
    }
    if (name != "")
    {
        return greeting(name);
    }
    if (number != 0)
    {
        return oddOrEven(number);
    }
    app.exit(CallForHelp());
    return 1;
}
