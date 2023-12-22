#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;


void find_adjacent_parts(int gear_pos, string line, vector<int>& parts)
{
    regex numbers ("\\d+");

    auto it = sregex_iterator(line.begin(), line.end(), numbers);
    for (; it != sregex_iterator() ; it++)
    {
        int match_pos = it->position();
        int match_len = it->length();

        if (match_pos <= (gear_pos + 1) && (match_pos + match_len - 1) >= (gear_pos - 1))
            parts.push_back(stoi(it->str()));
    }
}


int main(int argc, char** argv)
{
    int result = 0;
    ifstream file(argv[1]);
    if (file.is_open())
    {
        string line;
        getline(file, line);
        int columns = line.length();

        file.seekg(0, file.end);
        int file_length = file.tellg();
        file.seekg(0, file.beg);

        int rows = file_length / (columns + 1);  // Add 1 to account for the newline character.

        int row_sentinel = 0;

        regex gear ("([0-9]+)?(\\*)([0-9]+)?");

        while (getline( file, line ))
        {
            bool prev, next = false;
            string prev_line, next_line;

            if (row_sentinel > 0)
            {
                file.seekg((row_sentinel - 1) * (columns + 1), file.beg);
                getline(file, prev_line);
                prev = true;
            }

            if (row_sentinel < rows - 1)
            {
                file.seekg((row_sentinel + 1) * (columns + 1), file.beg);
                getline(file, next_line);
                next = true;
            }

            auto it = sregex_iterator(line.begin(), line.end(), gear);
            for (; it != sregex_iterator() ; it++)
            {
                vector<int> parts;

                int match_pos = it->position(2);

                if (!it->str(1).empty())
                    parts.push_back(stoi(it->str(1)));

                if (!it->str(3).empty())
                    parts.push_back(stoi(it->str(3)));

                // In the simplest case there is a part number either side of the asterisk on the same line. Beyond
                // that we'll need to explore the line above/below for other part numbers.
                if (prev && parts.size() < 2)
                    find_adjacent_parts(match_pos, prev_line, parts);

                if (next && parts.size() < 2)
                    find_adjacent_parts(match_pos, next_line, parts);

                if (parts.size() == 2)
                    result += parts[0] * parts[1];
            }

            row_sentinel++;
            file.seekg(row_sentinel * (columns + 1), file.beg);
        }
    }
    cout << result << endl;
    return 0;
}
