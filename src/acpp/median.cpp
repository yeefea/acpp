#include "median.h"

using std::domain_error;
using std::sort;
using std::vector;

double median(vector<double> vec)
{
    auto size = vec.size();
    if (size == 0)
    {
        throw domain_error("median of an empty vector");
    }
    sort(vec.begin(), vec.end());
    auto mid = size / 2;
    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}