#include <algorithm>
#include <unordered_map>
#include <limits>
#include <iostream>
using namespace std;
class Solution {
    unordered_map<long, long> f_map;
    long zeros(long x) {
        auto p = f_map.find(x);
        if (p != f_map.end()) {
            return p->second;
        }
        if (x <= 4) {
            f_map[x] = 0;
            return 0;
        }
        long c = x / 5;
        f_map[x] = c + zeros(x / 5);
        return f_map[x];
    }
public:
    int preimageSizeFZF(int k) {
        long en = k * 5 + 6;
        long be = 0;
        while (be + 1 < en) {
            long mid = (be + en) / 2;
            long mid_z = zeros(mid);
            if (mid_z > k) {
                en = mid;
            } else if (mid_z == k) {
                return 5;
            } else {
                be = mid;
            }
        }
        return 0;
    }
};