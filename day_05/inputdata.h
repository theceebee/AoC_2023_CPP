#include <utility>
#include <vector>
#include "rangedata.h"
#ifndef INPUTDATA_H
#define INPUTDATA_H
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

class InputData
{
    vector<RangeData>
        seed_to_soil_map,
        soil_to_fertilizer_map,
        fertilizer_to_water_map,
        water_to_light_map,
        light_to_temperature_map,
        temperature_to_humidity_map,
        humidity_to_location_map;

public:
    void append_range_data(long, long, long, InputDataType);
    long get_location_for_seed(long);
    vector<pair<long, long>> map_seeds_to_locations(long, long);
    void print();

private:
    vector<RangeData> &get_map_by_type(InputDataType);
};

#endif