#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long> sums(n + 1, 0);
        long sum = 0;
        sums[0] = 0;
        int res = 0;
        for (int i = 1; i <= n; i++) {
            sum += nums[i - 1];
            sums[i] = sum;
        }
        map<long, long> lower_set;
        lower_set[0] = 1;
        for (int hi = 0; hi < n; hi++) {
            long cur_sum = sums[hi + 1];
            long lower_bound = cur_sum  - upper;
            long higher_bound = cur_sum - lower;
            
            auto p  = lower_set.lower_bound(lower_bound);
            while (p!= lower_set.end() && (*p).first <= higher_bound) {
                res+= (*p).second;
                p++;
            }
            lower_set[cur_sum] = lower_set[cur_sum] + 1;

        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums {-2,5,-1};
    int lower = -2;
    int upper = 2;
    cout << s.countRangeSum(nums, lower, upper) << endl;
}