#include <fstream>
#include "inputdata.h"
#include "utils.h"

void parse_line(string line, vector<long> &result)
{
    long last = 0;
    string ss;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ' ')
        {
            ss = line.substr(last, i - last);
            result.push_back(stoul(ss));
            last = i;
        }
    }

    ss = line.substr(last);
    result.push_back(stoul(ss));
}
