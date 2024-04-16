#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int max_num = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > max_num) max_num = nums[i];
        }
        vector<int> diff(max_num + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                diff[abs(nums[i] - nums[j])]++;
            }
        }
        int total = 0;
        int i = 0;
        for (; i <= max_num; i++) {
            total += diff[i];
            if (total >= k) {
                return i;
            }
        }
        return i;
    }
};