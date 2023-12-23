#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <vector>
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
        // Start by initializing a vector to hold the card counts, with an initial value of 1 at each index.
        string line;
        getline(file, line);

        file.seekg(0, file.end);
        int file_size = file.tellg();

        file.seekg(0, file.beg);

        int line_count = file_size / (line.size() + 1);

        vector<int> cards(line_count, 1);

        for (int i = 0; i < line_count; ++i)
        {
            getline(file, line);

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

                // For every instance of the card at the current index we increment the next n cards (where n = count).
                // The nett result is to just add the value at the current index each of the next n indexes.
                for (int j = 0; j < count; ++j)
                    cards[i + j + 1] += cards[i];
            }
        }

        result = accumulate(cards.begin(), cards.end(), 0);
        cout << result << endl;
    }
    return 0;
}