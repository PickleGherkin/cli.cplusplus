#include "../include/CLI/CLI11.hpp"
#include "options.h"
#include <iostream>

int main(int argc, char **argv)
{
    CLI::App app{"CLI in C++"};
    argv = app.ensure_utf8(argv);
    std::string name = "";
    int number = -1;
    std::string gitRepoPath = "";

    app.add_option("-n, --name", name, "Name");
    app.add_option("-o, --oddOrEven", number, "Integer Number");
    app.add_option("-g, --showGitCommits", gitRepoPath, "Path to git repo");

    CLI11_PARSE(app, argc, argv);

    if (gitRepoPath != "")
    {
        int result = showGitCommits(gitRepoPath);
        if (result != 0)
        {
            std::cerr << "Error showing git commits." << std::endl;
            return result;
        }
        return 0;
    }
    if (name == "" && number == -1)
    {
        app.exit(CLI::CallForHelp());
        return 1;
    }
    oddOrEven(number);
    greeting(name);
    return 0;
}
