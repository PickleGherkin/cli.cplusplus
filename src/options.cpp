// https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170#predefined-macros
#ifdef _WIN32 // case when os is windows
#include <direct.h>
#define chdir _chdir // preprocessor alias for system functions because windows tends to be innovative, right?
#define popen _popen
#define pclose _pclose
#else // otherwise system functions from unix os
#include <unistd.h>
#endif

#include "options.h"
#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <map>
#include <cstdio>

using namespace std;

int oddOrEven(int number)
{
    string ooe = number % 2 == 0 ? "Even" : "Odd";
    cout << "Number is " << ooe << "." << endl;
    return 0;
}

int greeting(string name)
{
    cout << "Hello " << name << "!" << endl;
    return 0;
}

int gitxstat(const string &repoPath)
{
    // change cwd
    if (chdir(repoPath.c_str()) != 0)
    {
        cerr << "Failed to change directory to " << repoPath << endl;
        return 1;
    }
    array<char, 128> buffer;
    string result;
    // open pipe
    FILE *pipe = popen("git log --numstat", "r");
    if (!pipe)
    {
        cerr << "Error showing git commits: Failed to open process." << endl;
        return 1;
    }
    // read output
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
    {
        result += buffer.data();
    }
    // close pipe
    pclose(pipe);

    istringstream stream(result);
    string line;
    string author;
    int totalAdded = 0;
    map<string, int> authorContribution;
    // parse output
    while (getline(stream, line))
    {
        if (line.rfind("Author:", 0) == 0)
        {
            size_t start = 8;
            size_t end = line.find('<', start);
            if (end != string::npos)
                author = line.substr(start, end - start - 1);
            else
                author = line.substr(start);
            continue;
        }
        int added;
        char filename[1024];
        if (sscanf(line.c_str(), "%d%1023s", &added, filename) == 2)
        {
            totalAdded += added;
            authorContribution[author] += added;
        }
    }

    for (const auto &entry : authorContribution)
    {
        double percent = totalAdded > 0 ? (100.0 * entry.second / totalAdded) : 0.0;
        cout << entry.first << ": " << percent << "%" << endl;
    }
    return 0;
}