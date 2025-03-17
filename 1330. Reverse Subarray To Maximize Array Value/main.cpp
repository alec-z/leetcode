#include <vector>
#include <cmath>
using namespace std;
class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int sum_a = 0;
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            sum_a += abs(nums[i] - nums[i + 1]);
        }
        int max_increase = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i+1; j < n; j++) {
                int increase = 0;
                if (i > 0)
                    increase += abs(nums[j] - nums[i - 1]) - abs(nums[i] - nums[i - 1]);
                if (j < n - 1)
                    increase += abs(nums[i] - nums[j + 1]) - abs(nums[j] - nums[j + 1]);
                max_increase = max(max_increase, increase);
            }
        }
        return sum_a + max_increase;
    }
};