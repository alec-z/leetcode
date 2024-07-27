#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int f[n][2];
        f[0][0] = 0;
        f[0][1] = 1;
        for (int i = 1; i < n; i++) {
            f[i][0] = numeric_limits<int>::max();
            f[i][1] = numeric_limits<int>::max();
            if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]) {
                f[i][0] = min(f[i][0], f[i - 1][0]);
                f[i][1] = min(f[i][1], f[i - 1][1] + 1);
            }
            if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
                f[i][0] = min(f[i][0], f[i - 1][1]);
                f[i][1] = min(f[i][1], f[i - 1][0] + 1);
            }
        }
        bool flag = false;
        return min(f[n - 1][1], f[n - 1][0]);
        
    }
};