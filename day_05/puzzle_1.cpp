#include <iostream>
#include <fstream>
#include <limits>
#include <regex>
#include <string>
using namespace std;


enum InputDataType
{
    seed_to_soil = 0,
    soil_to_fertilizer = 1,
    fertilizer_to_water = 2,
    water_to_light = 3,
    light_to_temperature = 4,
    temperature_to_humidity = 5,
    humidity_to_location = 6
};


class RangeData
{
    uint dst_start, src_start, length;

    public:
        RangeData(uint dst_start, uint src_start, uint length) :
            dst_start{dst_start},
            src_start{src_start},
            length{length}
        {}

        uint remap_value(uint src)
        {
            uint result = src;

            if (this->src_start <= src && src <= this->src_start + this->length)
            {
                uint diff = src - this->src_start;
                result = this->dst_start + diff;
            }

            return result;
        }

        void print()
        {
            cout << this->dst_start << " " << this->src_start << " " << this->length << endl;
        }
};


class InputData
{
    vector<RangeData> seed_to_soil_map;
    vector<RangeData> soil_to_fertilizer_map;
    vector<RangeData> fertilizer_to_water_map;
    vector<RangeData> water_to_light_map;
    vector<RangeData> light_to_temperature_map;
    vector<RangeData> temperature_to_humidity_map;
    vector<RangeData> humidity_to_location_map;

    public:
        void append_range_data(uint, uint, uint, InputDataType);
        uint get_location_for_seed(uint);
        void print();
    
    private:
        vector<RangeData>& get_map_by_type(InputDataType);
};


vector<RangeData>& InputData::get_map_by_type(InputDataType type)
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


void InputData::append_range_data(
    uint dst_start,
    uint src_start,
    uint length,
    InputDataType type)
{
    RangeData data = RangeData(dst_start, src_start, length);
    vector<RangeData>& map = get_map_by_type(type);
    map.push_back(data);
}


uint InputData::get_location_for_seed(uint seed)
{
    uint temp, result = seed;

    for (int i = 0; i < 7; i++)
    {
        vector<RangeData> &map = get_map_by_type(static_cast<InputDataType>(i));
    
        for (auto data : map)
        {
            temp = data.remap_value(result);
            if (temp != result)
            {
                result = temp;
                break;
            }
        }
    }

    return result;
}


void InputData::print()
{
    cout << "seed-to-soil map:" << endl;
    for (auto i: this->seed_to_soil_map) { i.print(); }
    cout << endl;

    cout << "soil-to-fertilizer map:" << endl;
    for (auto i: this->soil_to_fertilizer_map) { i.print(); }
    cout << endl;

    cout << "fertilizer-to-water map:" << endl;
    for (auto i: this->fertilizer_to_water_map) { i.print(); }
    cout << endl;

    cout << "water-to-light map:" << endl;
    for (auto i: this->water_to_light_map) { i.print(); }
    cout << endl;

    cout << "light-to-temperature map:" << endl;
    for (auto i: this->light_to_temperature_map) { i.print(); }
    cout << endl;

    cout << "temperature-to-humidity map:" << endl;
    for (auto i: this->temperature_to_humidity_map) { i.print(); }
    cout << endl;

    cout << "humidity-to-location map:" << endl;
    for (auto i: this->humidity_to_location_map) { i.print(); }
}


void parse_line(string line, vector<uint> &result, char split_char = ' ')
{
    int last = 0;
    string ss;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == split_char)
        {
            ss = line.substr(last, i - last);
            result.push_back(stoul(ss));
            last = i;
        }
    }

    ss = line.substr(last);
    result.push_back(stoul(ss));
}


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
            vector<uint> seeds;
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
                    vector<uint> temp;
                    parse_line(line, temp);
                    data.append_range_data(
                        /*dst_start*/ temp[0],
                        /*src_start*/ temp[1],
                        /*length*/ temp[2],
                        /*type*/ static_cast<InputDataType>(type)
                    );
                }            
            }

            uint temp;
            uint result = numeric_limits<uint>::max();

            for (auto seed : seeds)
            {
                temp = data.get_location_for_seed(seed);
                if (temp < result)
                    result = temp;
            }

            cout << result << endl;
        }
    }
    return 0;
}