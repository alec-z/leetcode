#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        nums.push_back(-1);
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int j = i;
            while (nums[i] != -1 && nums[i] != i) {
                swap(nums[i], nums[nums[i]]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] == -1)
                return i;
        }
        return -1;
    }
};