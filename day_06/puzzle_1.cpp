#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


void parse_line(istream& stream, vector<uint>& container)
{
    string line, chomp;
    uint value;

    if (getline(stream, line))
    {
        stringstream ss(line);
        ss >> chomp;
        while (ss >> value)
            container.push_back(value);
    }
}


int main(int argc, char** argv)
{
    vector<uint> time, distance;
    uint result = 1;

    parse_line(cin, time);
    parse_line(cin, distance);

    for (int i = 0; i < time.size(); i++)
    {
        uint sentinel = 0;

        for (int j = 1; j < time[i]; j++)
        {
            uint temp = j * (time[i] - j);
            if (temp > distance[i])
                sentinel += 1;
        }

        result *= sentinel;
    }

    cout << "Puzzle 1: " << result << endl;

    return 0;
}