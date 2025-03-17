#include <vector>
#include <limits>
using namespace std;
const int MIN_INT = numeric_limits<int>::min();
class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size();
        int m = multipliers.size();
        vector<vector<int>>dp(m, vector<int>(m + 1, MIN_INT));
        dp[0][0] = multipliers[0] * nums[n - 1];
        dp[0][1] = multipliers[0] * nums[0];
        for (int i = 0; i < m - 1; i++) {
            for (int left = 0; left <= i + 1; left ++) {
                
                if (left < n) {
                    int l_v = nums[left];
                    dp[i + 1][left + 1] = max(dp[i + 1][left + 1], dp[i][left] + multipliers[i + 1] * l_v);
                }
                int right_pos = n - 1 - (i + 1) + left;
                if (right_pos >= 0) {
                    int r_v = nums[right_pos];
                    dp[i + 1][left] = max(dp[i + 1][left], dp[i][left] + multipliers[i + 1] * r_v);
                }
            }
        }
        return *max_element(dp[m - 1].begin(), dp[m - 1].end());
    }
};