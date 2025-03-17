#include <vector>
#include <limits>
using namespace std;
const int MIN_INT = numeric_limits<int>::min();
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        SubSol ss(stones);
        return ss.try_max_diff(stones.size());
    }
    class SubSol {
        int n;
        vector<int> stones;
        vector<int> sums;
        vector<int> pre_greater_sums;
        vector<int> h_m;
        public:
            SubSol(vector<int> & stones): stones(stones), n(stones.size()), sums(n + 1, 0),
             h_m(n + 1, MIN_INT),pre_greater_sums(n + 1, -1) {
                for (int i = 1; i <= n; i++) sums[i] = sums[i - 1] + stones[i - 1];
                int p = n;
                for (int i = n - 1; i >= 0; i--) {
                    if (sums[i] > sums[p]) {
                        pre_greater_sums[p] = i;
                        p = i;
                    }
                }
            }
            int try_max_diff(int len) {
                if (len == 1) return 0;
                if (h_m[len] > MIN_INT) return h_m[len];
                int max_s = MIN_INT;
                int i = n;
                for (; i >= n - len + 2; i = pre_greater_sums[i]) {
                    int left_sum = sums[i];
                    max_s = max(max_s, left_sum - try_max_diff(n - i + 1));
                }
                h_m[len] = max_s;
                return max_s;
            }
    };
};