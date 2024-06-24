#include <vector>
using namespace std;
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int len = nums.size();
        int total = 0;
        int be = 0;
        int en = 0;
        for (int i = 0; i < len; i++) {
            int cur = nums[i];
            if (i >= be && i < en) {
                cur = !cur;
            }
            if (cur == 0) {
                total++;
                int n_be = i;
                int n_en = i + k;

                if (n_be >= be && n_be <= en - 1) {
                    n_be = en;
                } else {
                    for (int j = be; j < en; j++)
                        nums[j] = !nums[j];
                }
                be = n_be;
                en = n_en;
                if (en > len) {
                    return -1;
                }
            }
        }
        return total;
    }
};

int main() {
    Solution s;
    vector<int> nums{0,1,0,0,1,0};
    s.minKBitFlips(nums, 4);
}