#include <iostream>
#include <cmath>
#include "inputdata.h"
using namespace std;

void InputData::append_range_data(long dst_start, long src_start, long length, InputDataType type)
{
    RangeData data = RangeData(dst_start, src_start, length);
    vector<RangeData>& map = get_map_by_type(type);
    map.push_back(data);
}

long InputData::get_location_for_seed(long seed)
{
    long temp, result = seed;

    for (int i = 0; i < 7; i++)
    {
        vector<RangeData> &map = get_map_by_type(static_cast<InputDataType>(i));
    
        for (auto data : map)
        {
            temp = data.map_src_to_dst(result);
            if (temp != result)
            {
                result = temp;
                break;
            }
        }
    }

    return result;
}

vector<pair<long, long>> InputData::map_seeds_to_locations(long begin, long count)
{
    vector<pair<long, long>> result;
    result.push_back({begin, count});

    // std::cout << "init start: " << begin << ", length: " << count << " (" << begin << " - " << begin + count - 1 << ")" << endl;

    for (int i = 0; i < 7; i++)
    {
        vector<pair<long, long>> temp(result);
        result.clear();

        vector<RangeData> &map = get_map_by_type(static_cast<InputDataType>(i));

        while (!temp.empty())
        {
            bool remapped = false;
            pair<long, long> input = temp.back(); // the source range data
            temp.pop_back();

            long input_start = input.first;
            long input_end = input.first + input.second - 1;
            
            // cout << "input: " << input.first << " " << input.second << " (" << input_start << " - " << input_end << ")" << endl;

            for (auto range_data : map)
            {
                // cout << "range data: " << range_data.get_src_start() << " " << range_data.get_length() << " (" << range_data.get_src_start() << " - " << range_data.get_src_end() << ")" << endl;
                if (input_start <= range_data.get_src_end() && range_data.get_src_start() <= input_end) // There is some overlap.
                {
                    // Push any part of the input range that preceeds the remap range back to the temp vector. 
                    if (input_start < range_data.get_src_start())
                    {
                        long start_diff = range_data.get_src_start() - input_start;
                        result.push_back({input_start, start_diff});
                        input_start = range_data.get_src_start();
                    }

                    //  Insert any part of the input range that overlaps the remap range.
                    long remapped_start = range_data.map_src_to_dst(input_start);
                    long remapped_end = range_data.map_src_to_dst(min(input_end, range_data.get_src_end()));
                    result.push_back({remapped_start, remapped_end - remapped_start + 1});

                    // Insert any part of the input range that exceeds the remap range. 
                    if (input_end > range_data.get_src_end())
                    {
                        long end_diff = input_end - range_data.get_src_end();
                        result.push_back({range_data.get_src_end() + 1, end_diff});
                    }

                    remapped = true;
                }
            }

            if (!remapped)
                result.push_back(input);
        }

        // std::cout << i << endl;
        // for (auto r : result)
        //     std::cout << "start: " << r.first << ", length: " << r.second << " (" << r.first << " - " << r.first + r.second - 1 << ")" << endl;
    }

    return result;
}

void InputData::print()
{
    std::cout << "seed-to-soil map:" << endl;
    for (auto i: this->seed_to_soil_map) { i.print(); }
    std::cout << endl;

    std::cout << "soil-to-fertilizer map:" << endl;
    for (auto i: this->soil_to_fertilizer_map) { i.print(); }
    std::cout << endl;

    std::cout << "fertilizer-to-water map:" << endl;
    for (auto i: this->fertilizer_to_water_map) { i.print(); }
    std::cout << endl;

    std::cout << "water-to-light map:" << endl;
    for (auto i: this->water_to_light_map) { i.print(); }
    std::cout << endl;

    std::cout << "light-to-temperature map:" << endl;
    for (auto i: this->light_to_temperature_map) { i.print(); }
    std::cout << endl;

    std::cout << "temperature-to-humidity map:" << endl;
    for (auto i: this->temperature_to_humidity_map) { i.print(); }
    std::cout << endl;

    std::cout << "humidity-to-location map:" << endl;
    for (auto i: this->humidity_to_location_map) { i.print(); }
}

vector<RangeData> &InputData::get_map_by_type(InputDataType type)
{
    switch (type) {
        case InputDataType::seed_to_soil:
            return this->seed_to_soil_map;

        case InputDataType::soil_to_fertilizer:
            return this->soil_to_fertilizer_map;

        case InputDataType::fertilizer_to_water:
            return this->fertilizer_to_water_map;

        case InputDataType::water_to_light:
            return this->water_to_light_map;

        case InputDataType::light_to_temperature:
            return this->light_to_temperature_map;

        case InputDataType::temperature_to_humidity:
            return this->temperature_to_humidity_map;

        case InputDataType::humidity_to_location:
            return this->humidity_to_location_map;
    };

    abort();
};
