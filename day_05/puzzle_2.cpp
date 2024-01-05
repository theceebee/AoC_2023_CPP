#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include "utils.h"
using namespace std;

vector<Range> get_seeds(ifstream &input)
{
    vector<Range> result;
    string line, chomp;

    getline(input, line);
    istringstream ss(line);

    // Chomp the start of the line.
    ss >> chomp;

    long long start, length;

    while (ss >> start >> length)
    {
        result.push_back({start, length});
    }

    // Chomp the empty line.
    getline(input, chomp);

    return result;
}


int main(int argc, char **argv)
{
    ifstream file(argv[1]);
    if (file.is_open())
    {
        const auto seeds = get_seeds(file);
        const auto seed_to_soil = get_mappings(file);
        const auto soil_to_fertilizer = get_mappings(file);
        const auto fertilizer_to_water = get_mappings(file);
        const auto water_to_light = get_mappings(file);
        const auto light_to_temperature = get_mappings(file);
        const auto temperature_to_humidity = get_mappings(file);
        const auto humidity_to_location = get_mappings(file);

        const auto soils = remap(seeds, seed_to_soil);
        const auto fertilizers = remap(soils, soil_to_fertilizer);
        const auto waters = remap(fertilizers, fertilizer_to_water);
        const auto lights = remap(waters, water_to_light);
        const auto temperatures = remap(lights, light_to_temperature);
        const auto humidities = remap(temperatures, temperature_to_humidity);
        const auto locations = remap(humidities, humidity_to_location);

        long long lowest_location = numeric_limits<long long>::max();

        for (auto location: locations)
        {
            if (location.start < lowest_location)
            {
                lowest_location = location.start;
            }
        }

        cout << lowest_location << endl;
    }
    return 0;
}
