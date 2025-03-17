#include <vector>
#include <limits>
using namespace std;
const int MIN_INT = numeric_limits<int>::min();
class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        SubSol ss(stoneValue);
        return ss.try_max_score(0, stoneValue.size() - 1);
    }
    class SubSol {
        vector<int> & stones;
        int n;
        vector<vector<int> > h_m;
        vector<int> sums;
        public:
            SubSol(vector<int> & stones): stones(stones),n(stones.size()), h_m(n, vector<int> (n, 0)), sums(n + 1, 0) {
                for (int i = 1; i <= n; i++) sums[i] = sums[i - 1] + stones[i - 1];
            }
            int try_max_score(int be, int en) {
                if (en <= be) {
                    return 0;
                }
                if (h_m[be][en] > 0 ) {
                    return h_m[be][en];
                }
                int max_s = MIN_INT;
                for (int k = be; k < en; k++) {
                    int left = sums[k + 1] - sums[be]; 
                    int right = sums[en + 1] - sums[k + 1];
                    if (left < right) {
                        max_s = max(max_s, left + try_max_score(be, k));
                    } else if (left > right) {
                        max_s = max(max_s, right + try_max_score(k + 1, en));
                    } else {
                        max_s = max(max_s, left + max(try_max_score(be, k), try_max_score(k + 1, en)));
                    }
                }
                h_m[be][en] = max_s;
                return max_s;
            }
    };
};