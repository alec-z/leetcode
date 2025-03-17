#include <vector>
#include <limits>
using namespace std;
const int MIN_INT = numeric_limits<int>::min();
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> sums(n + 1, 0);
        vector<int> f_m(n + 1, MIN_INT);
        for (int i = 1; i < n + 1; i++) {
            sums[i] = sums[i - 1] + stones[i - 1];
        }
        f_m[n] = 0;
        int max_s = sums[n] - f_m[n];
        for (int i = n - 1; i >= 1; i--) {
            max_s = max(max_s, sums[i + 1] - f_m[i + 1]);
            f_m[i] = max_s; 
        }
        return f_m[1];
    }
    
};