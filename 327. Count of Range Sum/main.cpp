#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> sums(n + 1, 0);
        long long sum = 0;
        sums[0] = 0;
        int res = 0;
        for (int i = 1; i <= n; i++) {
            sum += nums[i - 1];
            sums[i] = sum;
        }
        int p = 0;
        for (int lo = 0; lo < n; lo++) {
            for (int hi = lo; hi < n; hi++) {
                long long cur_val = (sums[hi + 1] - sums[lo]);
                if (cur_val >= lower && cur_val <= upper) {
                    res ++;
                }
            }
        }
        
        return res++;
    }
};

int main() {
    Solution s;
    vector<int> nums {-2147483647,0,-2147483647,2147483647};
    int lower = -564;
    int upper = 3864;
    cout << s.countRangeSum(nums, lower, upper) << endl;
}