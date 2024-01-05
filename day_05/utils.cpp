#include <sstream>
#include "utils.h"
using namespace std;

vector<RangeMapping> get_mappings(ifstream &input)
{
    vector<RangeMapping> result;
    string line;
    long long dst_start, src_start, length;

    // Chomp the header line.
    getline(input, line);

    while (getline(input, line) && line != "")
    {
        istringstream ss(line);
        while (ss >> dst_start >> src_start>> length)
        {
            result.push_back({dst_start, src_start, length});
        }
    }

    return result;
}

vector<Range> remap(vector<Range> ranges, vector<RangeMapping> mappings)
{
    vector<Range> result, temp(ranges);

    while (!temp.empty())
    {
        Range range = temp.back();
        temp.pop_back();
        bool remapped = false;

        for (auto mapping : mappings)
        {
            long long range_start = range.start;
            long long range_end = range_start + range.length - 1;
            long long mapping_src_end = mapping.src_start + mapping.length - 1;
            long long mapping_dst_end = mapping.dst_start + mapping.length - 1;

            // Check for an overlap.
            if (range_start <= mapping_src_end && mapping.src_start <= range_end)
            {
                if (range_start < mapping.src_start)
                {
                    temp.push_back({range_start, mapping.src_start - range_start});
                    range_start = mapping.src_start;
                }

                if (range_end > mapping_src_end)
                {
                    temp.push_back({mapping_src_end + 1, range_end - mapping_src_end});
                }

                long long diff = mapping.dst_start - mapping.src_start;
                long long remap_start = range_start + diff;
                long long remap_end = min(range_end + diff, mapping_dst_end);
                long long remap_length = remap_end - remap_start + 1;
                result.push_back({remap_start, remap_length});
                remapped = true;
                break;
            }
        }

        if (!remapped)
            result.push_back(range);
    }

    return result;
}
