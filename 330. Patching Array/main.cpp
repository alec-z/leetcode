#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int res = 0;
        long long upper = 0;
        for (int i = 0; i < nums.size() && upper < n; i++) {
            if (upper + 1 >= nums[i]) {
                upper += nums[i];
            } else {
                while (upper + 1 < nums[i] && upper < n) {
                    upper += (upper + 1);
                    res++;
                }
                upper += nums[i];
            }
        }
        while (upper < n) {
            upper += (upper + 1);
            res++;
        }
        return res;
    }
};

int main() {
    vector<int> nums {1,2,2};
    int n = 5;
    Solution s;
    cout << s.minPatches(nums, n) << endl;

}