#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
using namespace std;


set<int> parse_numbers(string input)
{
    set<int> result;

    regex pattern("\\d+");

    auto it = sregex_iterator(input.begin(), input.end(), pattern);
    for (; it != sregex_iterator(); ++it)
        result.insert(stoi(it->str()));
        it++;

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
            regex pattern("Card\\s+[0-9]+:([\\s\\d]+)\\|([\\s\\d]+)");
            smatch sm;  

            if (regex_match(line, sm, pattern))
            {
                set<int> winning_numbers = parse_numbers(sm.str(1));
                set<int> drawn_numbers = parse_numbers(sm.str(2));

                int count = 0;
                for (auto it : drawn_numbers)
                {
                    auto search = winning_numbers.find(it);
                    if (search != winning_numbers.end())
                        count++;
                }

                result += (count) ? pow(2, count - 1) : 0;
            }
        }
    }
    cout << result << endl;
    return 0;
}