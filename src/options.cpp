#include "options.h"
#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;

void oddOrEven(int number)
{
    if (number == -1)
    {
        return;
    }
    string ooe = number % 2 == 0 ? "Even" : "Odd";
    cout << "Number is " << ooe << "." << endl;
}

void greeting(string name)
{
    if (name == "")
    {
        return;
    }
    cout << "Hello " << name << "!" << endl;
}

int showGitCommits(const string& repoPath)
{
    // change cwd
    if (chdir(repoPath.c_str()) != 0)
    {
        cerr << "Failed to change directory to " << repoPath << endl;
        return 1;
    }
    // prepare
    array<char, 128> buffer;
    string result;
    // open pipe
    FILE* pipe = popen("git log --numstat", "r");
    if (!pipe)
    {
        cerr << "Failed to open process." << endl;
        return 1;
    }
    // read output
    while(fgets(buffer.data(), buffer.size(), pipe) != nullptr)
    {
        result += buffer.data();
    }
    // close pipe
    pclose(pipe);

    istringstream stream(result);
    string line;
    int totalAdded = 0;
    // parse output
    while (getline(stream, line)) {
        int added, removed;
        char filename[1024];
        if (sscanf(line.c_str(), "%d%d%1023s", &added, &removed, filename) == 3) {
            totalAdded += added;
        }
    }
    cout << "Added Lines: " << totalAdded << endl;
    return 0;
}