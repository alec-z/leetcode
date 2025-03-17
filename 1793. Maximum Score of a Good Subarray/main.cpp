#include <vector>
using namespace std;
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int i = k - 1;
        int j = k + 1;
        int min_v = nums[k];
        int res = min_v;
        while (true) {
            while (i >= 0 && nums[i] >= min_v) i--;
            while (j <= n - 1 && nums[j] >= min_v) j++;
            res = max(res, min_v * (j - i - 1));
            if (i == -1 && j == n) return res;
            if (i == -1) {
                min_v = nums[j];
                j++;
            } else if (j == -1) {
                min_v = nums[i];
                i--;
            } else {
                if (nums[i] > nums[j]) {
                    min_v = nums[i];
                    i--;
                } else {
                    min_v = nums[j];
                    j++;
                }
            }
        }
        return 0;
    }
};