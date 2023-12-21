#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
using namespace std;


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

        regex numbers ("\\d+");
        regex symbols("[^.0-9]");
        smatch sm;

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

            auto it = sregex_iterator(line.begin(), line.end(), numbers);
            for (; it != sregex_iterator() ; it++)
            {
                bool is_part_number = false;

                int match_pos = it->position();
                int match_len = it->length();

                // We need the diagonally adjacent chars, but we need to account for the case where the number starts
                // at the 0th index in the sequence.
                int substr_pos = fmax(0, match_pos - 1);
                int substr_len = match_len + (match_pos == 0 ? 1 : 2);

                string adjacent_line;
                string adjacent_substr;

                // Check the prev row.
                if (prev)
                {
                    adjacent_substr = prev_line.substr(substr_pos, substr_len);
                    regex_search(adjacent_substr, sm, symbols);
                    if (!sm.empty())
                        is_part_number = true;
                }

                // Check the current row, first checking for any symbol immediately before the number...
                if (!is_part_number && match_pos != 0 && line[match_pos - 1] != '.')
                    is_part_number = true;

                // ... and then immediately after it.
                if (!is_part_number && match_pos + match_len != columns && line[match_pos + match_len] != '.')
                    is_part_number = true;

                // Check the next row.
                if (!is_part_number && next)
                {
                    adjacent_substr = next_line.substr(substr_pos, substr_len);
                    regex_search(adjacent_substr, sm, symbols);
                    if (!sm.empty())
                        is_part_number = true;
                }

                if (is_part_number)
                    result += stoi(it->str());
            }

            row_sentinel++;
            file.seekg(row_sentinel * (columns + 1), file.beg);
        }
    }
    cout << result << endl;
    return 0;
}
