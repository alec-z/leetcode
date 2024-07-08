#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

class Solution {
    long n;
    long k;
    long findShortest(vector<long> & sums, long be, long en) {
        if (be > en) return -1;
        long s = (be + en) / 2;
        bool mid_ok = false;
        bool greater_mid_ok = false;
        bool less_mid_ok = false;
        if (s > 1 && s - 1 >= be) {
            set<long> less_mid_sums_set = { 0 };
            // distance from be ~ (s -1)   i - (s - 1) ~ i - be
            // i - (s - 1) == 0 i = s - 1

            for (long i = be; i < n + 1; i++) {
                if (sums[i] - *(less_mid_sums_set.begin()) >= k) {
                    less_mid_ok = true;
                    break;
                } else {
                    if (i >= s - 1)
                        less_mid_sums_set.erase(sums[i + 1 - s]);
                    less_mid_sums_set.insert(sums[i + 1 - be]);
                }
            }
        }
        if (less_mid_ok) return findShortest(sums, be, s - 1);
        else {
            for (long i = s; i < n + 1; i++) {
                if (sums[i] - sums[i - s] >= k) {
                    mid_ok = true;
                    break;
                }
            }
            if (mid_ok) return s;
            else return findShortest(sums, s + 1, en);
        }
        return -1;
    }
public:
    int shortestSubarray(vector<int>& nums, long k) {
        n = nums.size();
        this -> k = k;
        vector<long> sums(n + 1, 0);
        for (int i = 1; i < n + 1; i++) {
            sums[i] = sums[i - 1] + nums[i-1];
        }
        return findShortest(sums, 1, n);
    }
};


int main() {
    vector<int> nums = {84,-37,32,40,95};
    int k = 167;
    Solution s;
    cout << s.shortestSubarray(nums, 167);
}