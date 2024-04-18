#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;
const double eps = 1e-6;
class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int nums_len = nums.size();
        if (nums_len == 1) return false;
        vector<int> prefix_sum(nums_len + 1, 0);
        prefix_sum[0] = 0;
        for (int i = 1; i <= nums_len; i++) prefix_sum[i] = nums[i - 1] + prefix_sum[i - 1];
        double avg = (double)prefix_sum[prefix_sum.size() - 1] / nums_len;
        int consider_max_len = (nums_len + 1) / 2;
        vector<double> sum_with_len(consider_max_len + 1);
        
        for (int i = 1; i <= consider_max_len; i++) {
            sum_with_len[i] = avg * i;
        }

        vector<vector<bool>> pre_s(nums_len), cur_s(nums_len);
        for (int upper = 0; upper < nums_len; upper++) {
            pre_s[upper].resize(prefix_sum[1] + 1, false);
            if (upper > 0) pre_s[upper] = pre_s[upper - 1];
            pre_s[upper][nums[upper]] = true;
            if (abs(nums[upper] - sum_with_len[1]) < eps) {
                return true;
            }
        }


        for (int s = 2; s <= consider_max_len; s++) {
            for (int upper = 0; upper < nums_len; upper++) cur_s[upper].resize(prefix_sum[s] + 1, false);
            for (int upper = s - 1; upper < nums_len; upper++) {
                cur_s[upper] = cur_s[upper - 1];
                for (int k = 0; k <= prefix_sum[s - 1]; k++) {
                    if (pre_s[upper - 1][k]) {
                        int new_val = k + nums[upper];
                        cur_s[upper][new_val] = true;
                        if (abs(new_val - sum_with_len[s]) < eps) {
                            return true;
                        }
                    }
                }
            }
            pre_s = cur_s;
        }
        return false;
    }
};

int main() {
    vector<int> nums{72,56,81,54,15,96,80,90,8};
    Solution s;
    cout << s.splitArraySameAverage(nums) << endl;
}