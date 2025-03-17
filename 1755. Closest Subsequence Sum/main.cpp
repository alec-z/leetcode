#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        sort(nums.begin(), nums.end());
        int len = nums.size();
        int h_len = len / 2;
        int max_num = pow(2, h_len);
        vector<int> sums(max_num, 0);
        for (unsigned mask = 0; mask < max_num; mask++) {
            int sum = 0;
            for (unsigned j = 0; j < h_len; j++) {
                if (mask & (1 << j)) sum += nums[j];
            }
            sums[mask] = sum;
        }
        sort(sums.begin(), sums.end());
        int slow = 0;
        for (int fast = 1; fast < sums.size(); fast++) {
            if (sums[slow] != sums[fast]) {
                slow++;
                sums[slow] = sums[fast];
            }
        }
        sums.resize(slow+1);

        max_num = pow(2,len -  h_len);
        int res = 1e9 + 1;
        for (unsigned mask = 0; mask < max_num; mask++) {
            int sum = 0;
            for (unsigned j = 0; j < len -  h_len; j++) {
                if (mask & (1 << j)) sum += nums[h_len + j];
            }

            auto p = lower_bound(sums.begin(), sums.end(), goal - sum);
            if (p != sums.end()) {
                res = min(res, *p + sum - goal);
            }
            if (p != sums.begin()) {
                p--;
                res = min(res, goal - *p - sum);
            }
            if (res == 0) {
                return 0;
            }
        }
        return res;
    }
};