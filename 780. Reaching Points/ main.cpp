#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while ((tx >= sx && ty >= sy) && (tx > sx || ty > sy)) {
            if (tx == ty) return false;
            if (tx > ty) { // x  = x + y; y = y;
                tx = tx  - max(((tx - sx) / ty), 1) * ty;
            } else if (tx < ty){ // x = x; y = x + y;
                ty = ty -  max(((ty - sy) / tx), 1) * tx;
            }
        }
        return (tx == sx && ty == sy);
    }
};
