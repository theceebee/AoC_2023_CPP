#include <fstream>
#include <vector>
#ifndef UTILS_H
#define UTILS_H
using namespace std;

struct Range {
    long long start;
    long long length;
};

struct RangeMapping {
    long long dst_start;
    long long src_start;
    long long length;
};

vector<RangeMapping> get_mappings(ifstream &);
vector<Range> remap(vector<Range>, vector<RangeMapping>);

#endif