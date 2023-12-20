#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <regex>
using namespace std;


int main(int argc, char** argv)
{
    ifstream file (argv[1]);
    if (file.is_open())
    {
        int result = 0;
        queue<string> buffer;
        string line;

        vector<int> symbol_indexes_a;
        vector<int> symbol_indexes_b;

        regex numbers ("\\d+");

        while (getline( file, line ))
        {
            buffer.push(line);

            cout << line << endl;
            auto it = sregex_iterator(line.begin(), line.end(), numbers);
            for (; it != sregex_iterator() ; it++)
            {
                cout << "number: " << it->str() << " position: " << it->position() << " length: " << it->length() << endl;

                // Use a sentinel to ensure that we don't
                bool sentinel = false;

                // Check for any symbol infront of the number.
                if (it->position() != 0)
                {

                }



                switch (it->position())
                {
                    case 0:
                        break;
                    case (line.length() - it->length()):
                        break;
                    default:

                }

                
            
            }

            if (buffer.size() > 1)
            {
                buffer.pop();
            }
        }
    }
    return 0;
}
