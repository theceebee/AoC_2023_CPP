#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;


int processToken(string s)
{
    if (s == "one") {
        return 1;
    } else if (s == "two") {
        return 2;
    } else if (s == "three") {
        return 3;
    } else if (s == "four") {
        return 4;
    } else if (s == "five") {
        return 5;
    } else if (s == "six") {
        return 6;
    } else if (s == "seven") {
        return 7;
    } else if (s == "eight") {
        return 8;
    } else if (s == "nine") {
        return 9;
    } else {
        return s[0] - '0';
    }
}


int main(int argc, char** argv)
{
    string line;
    ifstream file (argv[1]);
    if (file.is_open())
    {
        int result = 0;
        string prefix = "^.*";
        string suffix = "(one|two|three|four|five|six|seven|eight|nine|[1-9])";
        regex startPattern(prefix + "?" + suffix);  // non-greedy
        regex endPattern(prefix + suffix);  // greedy

        smatch startMatch;
        smatch endMatch;

        while ( getline(file, line) )
        {

            regex_search(line, startMatch, startPattern);
            regex_search(line, endMatch, endPattern);

            int a = processToken(startMatch.str(1));
            int b = processToken(endMatch.str(1));

            result += (a * 10) + b;
        }

        cout << result << endl;
    }
}
