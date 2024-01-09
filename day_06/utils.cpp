#include "utils.h"

long get_distance_travelled(long time_pressed, long total_time)
{
    return time_pressed * (total_time - time_pressed);
}
