#ifndef RANGEDATA_H
#define RANGEDATA_H

class RangeData
{
    long dst_start, src_start, length;

    public:
        RangeData(long, long, long);

        long get_dst_start();
        long get_dst_end();
        long get_src_start();
        long get_src_end();
        long get_length();

        void print();
        long map_src_to_dst(long);
        long map_dst_to_src(long);
};

#endif
