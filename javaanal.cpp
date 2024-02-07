#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string assertSynthesizer1(string condition)
{
    string assertion = "assert(!(" + condition + "));";
    return assertion;
}

string assertSynthesizer2(string condition)
{
    string assertion = "assert(!(!(" + condition + ")));";
    return assertion;
}

int main()
{
    string line;
    vector<string> conditions;

    ifstream infile("test.java");
    if (!infile.is_open()) {
        cout << "Unable to open file" << endl;
        return 1;
    }

    while (getline(infile, line)) {
        // Look for lines that contain conditional expressions
        if (line.find("if") != string::npos || line.find("while") != string::npos || line.find("for") != string::npos) {
            size_t start = line.find_first_of('(') + 1;
            size_t end = line.find_last_of(')');
            string condition = line.substr(start, end - start);
            conditions.push_back(condition);
        }
    }

    infile.close();

    ofstream outfile("assertions.java");
    if (!outfile.is_open()) {
        cout << "Unable to create output file" << endl;
        return 1;
    }

    for (const auto& condition : conditions) {
        outfile << assertSynthesizer1(condition) << endl;
        outfile << assertSynthesizer2(condition) << endl;
    }

    outfile.close();

    return 0;
}
