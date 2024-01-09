#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"
using namespace std;


long parse_line(istream& stream)
{
    string line, chomp, token, result;

    if (getline(stream, line))
    {
        stringstream ss(line);
        ss >> chomp;
        while (ss >> token)
            result += token;
    }

    return stol(result);
}


int main(int argc, char** argv)
{
    long total_time = parse_line(cin);
    long distance_record = parse_line(cin);

    int chunk_count = 5;
    long chunk_size = total_time / chunk_count;

    long time_pressed, distance_travelled;
    long range_start, range_start_near_miss, range_end, range_end_near_miss;
    range_start_near_miss = 0;
    range_end_near_miss = total_time;
    range_start = -1, range_end = -1;

    for (int i = 1; i < chunk_count; i++)
    {
        time_pressed = chunk_size * i;
        distance_travelled = get_distance_travelled(time_pressed, total_time);

        if (distance_travelled > distance_record)  // success
        {
            if (range_start < range_start_near_miss)  // this should only be true once, for the first hit
            {
                range_start = time_pressed;
            }

            range_end = time_pressed;
        }
        else  // failure
        {
            if (range_start < range_start_near_miss)  // this should be true *until* we get the first hit
            {
                range_start_near_miss = time_pressed;
            }
        }
    }

    int result;

    if (range_start >= 0 && range_end >= 0)
    {
        long temp;

        while (range_start - range_start_near_miss > 1)
        {
            time_pressed = range_start_near_miss + (range_start - range_start_near_miss) / 2;
            distance_travelled = get_distance_travelled(time_pressed, total_time);

            if (distance_travelled > distance_record)
            {
                range_start = time_pressed;
            }
            else
            {
                range_start_near_miss = time_pressed;
            }
        }

        while (range_end_near_miss - range_end > 1)
        {
            time_pressed = range_end + (range_end_near_miss - range_end) / 2;
            distance_travelled = get_distance_travelled(time_pressed, total_time);

            if (distance_travelled > distance_record)
            {
                range_end = time_pressed;
            }
            else
            {
                range_end_near_miss = time_pressed;
            }
        }

        cout << "Puzzle 2: " << range_end - range_start + 1 << endl;

        result = 0;
    }
    else
    {
        result = 1;
    }

    return result;
}