#include <iostream>
#include "rangedata.h"
using namespace std;


RangeData::RangeData(long dst_start, long src_start, long length)
{
    this->dst_start = dst_start;
    this->src_start = src_start;
    this->length = length;
}

long RangeData::get_dst_start()
{
    return dst_start;
}

long RangeData::get_dst_end()
{
    return dst_start + length - 1;
}

long RangeData::get_src_start()
{
    return src_start;
}

long RangeData::get_src_end()
{
    return src_start + length - 1;
}

long RangeData::get_length()
{
    return length;
}

void RangeData::print()
{
    cout << dst_start << " " << src_start << " " << length << endl;
}

long RangeData::map_src_to_dst(long src)
{
    long result = src;

    if (src_start <= src && src <= src_start + length)
        result = dst_start + src - src_start;

    return result;
}

long RangeData::map_dst_to_src(long dst)
{
    long result = dst;

    if (dst_start <= dst && dst <= dst_start + length)
        result = src_start + dst - dst_start;

    return result;
}
