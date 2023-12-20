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

        while ( getline(file, line) )
        {
            smatch sm;
            regex pattern("one|two|three|four|five|six|seven|eight|nine|[1-9]");
            regex_search(line, sm, pattern);

            int a = processToken(sm.str());
            int b;

            size_t len = line.size();
            for (int i = 1; i <= len; i++)
            {
                string ss = line.substr(len - i, i);
                regex_search(ss, sm, pattern);
                if (!sm.empty())
                {
                    b = processToken(sm.str());
                    break;
                }
            }

            result += (a * 10) + b;
        }

        cout << result << endl;
    }
}
