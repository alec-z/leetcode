#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] == i + 1) continue;
            int j = i;
            while (nums[j]  != j + 1) {
                if (nums[j]>= 1 && nums[j] < n + 1)
                    if (nums[nums[j] - 1] !=  nums[j]) {
                        swap(nums[nums[j] - 1], nums[j]);
                    } else break;
                else {
                    break;
                }
            }
        }
        for (int i = 0; i <n ; i++) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
        
    }
};