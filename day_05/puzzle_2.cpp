#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
#include "inputdata.h"
#include "utils.h"
using namespace std;


int main(int argc, char** argv)
{
    if (argc == 2)
    {
        ifstream file(argv[1]);
        if (file.is_open())
        {
            InputData data;
            string line;

            // Get the seeds.
            getline(file, line);

            int i = line.find_first_of(' ');
            vector<long> seeds;
            parse_line(line.substr(i + 1), seeds);

            int type = -1;

            while (getline(file, line))
            {
                if (line.length() == 0)
                {
                    // chomp the header line
                    getline(file, line);

                    // increment the type
                    type++;
                }
                else
                {
                    vector<long> temp;
                    parse_line(line, temp);
                    data.append_range_data(
                        /*dst_start*/ temp[0],
                        /*src_start*/ temp[1],
                        /*length*/ temp[2],
                        /*type*/ static_cast<InputDataType>(type)
                    );
                }            
            }

            long result = numeric_limits<long>::max();

            for (int j = 0; j < seeds.size() / 2; j++)
            {
                for (pair<long, long> locations : data.map_seeds_to_locations(seeds[j * 2], seeds[j * 2 + 1]))
                {
                    if (locations.first < result)
                        result = locations.first;
                }
            }

            cout << result << endl;
        }
    }
    return 0;
}