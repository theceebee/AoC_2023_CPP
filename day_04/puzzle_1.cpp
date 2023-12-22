#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <regex>
using namespace std;


set<int> parse_numbers(string input)
{
    set<int> result;
    return result;
}


int main(int argc, char** argv)
{
    int result = 0;

    ifstream file(argv[1]);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;

            regex pattern("Card\\s+[0-9]+:([\\s\\d]+)\\|([\\s\\d]+)");
            smatch sm;  

            if (regex_match(line, sm, pattern))
            {
                set<int> winning_numbers = parse_numbers(sm.str(1));
                set<int> drawn_numbers = parse_numbers(sm.str(2));
            }
        }
    }

    return result;
}