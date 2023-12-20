#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;


int processLine(string line) {

    int minR, minG, minB = 0;

    regex indexPattern("Game ([0-9]+):\\s");
    regex setPattern("\\s?([^;]+);?");
    regex tokenPattern("\\s?([0-9]+)\\s(red|green|blue),?");

    smatch indexMatch;
    regex_search(line, indexMatch, indexPattern);

    string setSubstr = line.substr(indexMatch.length());
    auto setIter = sregex_iterator(setSubstr.begin(), setSubstr.end(), setPattern);

    while (setIter != sregex_iterator())
    {
        string setSubstr = setIter->str(1);
        auto tokenIter = sregex_iterator(setSubstr.begin(), setSubstr.end(), tokenPattern);

        while (tokenIter != sregex_iterator())
        {
            int count = stoi(tokenIter->str(1));
            string colour = tokenIter->str(2);

            if (colour == "red" && count > minR)
                minR = count;
            else if (colour == "green" && count > minG)
                minG = count;
            else if (colour == "blue" && count > minB)
                minB = count;

            tokenIter++;
        }

        setIter++;
    }

    return minR * minG * minB;
}


int main(int argc, char** argv)
{
    int result = 0;
    ifstream file (argv[1]);
    if (file.is_open())
    {
        string line;
        while ( getline(file, line) )
        {
            result += processLine(line);
        }
    }
    cout << result << endl;
    return 0;
}
