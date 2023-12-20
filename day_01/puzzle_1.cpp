#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;


int main(int argc, char** argv)
{
    string line;
    ifstream file (argv[1]);
    if (file.is_open())
    {
        int result = 0;

        while ( getline(file, line) )
        {
            int a, b;
            bool sentinel = false;

            for (int i = 0; i < line.size(); i++)
            {
                {
                    if ( isdigit(line[i]) )
                    {
                        if (!sentinel)
                        {
                            a = line[i] - '0';
                            sentinel = true;
                        }
                        b = line[i] - '0';
                    }
                }
            }

            result += (a * 10) + b;
        }
        cout << result << endl;
    }
}
