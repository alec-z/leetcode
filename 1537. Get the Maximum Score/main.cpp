#include <vector>
using namespace std;
const long mod_p = 1e9 + 7;
class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size();
        int l2 = nums2.size();
        vector<vector<vector<long> > > dp(2, vector<vector<long>>(l2 + 1, vector<long>(2, 0)));
        for (int j = 1; j <= l2; j++) {
            dp[0][j][1] = dp[0][j-1][1] + nums2[j - 1];
        }

        for (int i = 1; i <= l1; i++) {
            for (int j = 1; j <= l2; j++) {
                dp[i & 1][j][0] = max(dp[i & 1][j][0], dp[i & 1][j - 1][0]);
                dp[i & 1][j][0] = max(dp[i & 1][j][0], dp[(i - 1) & 1][j][0] + nums1[i - 1]);
                dp[i & 1][j][1] = max(dp[i & 1][j][1], dp[(i - 1) & 1][j][1]);
                dp[i & 1][j][1] = max(dp[i & 1][j][1], dp[i & 1][j - 1][1] + nums2[j - 1]);
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i & 1][j][1] = max(dp[i & 1][j][1],  dp[i & 1][j][0]);
                    dp[i & 1][j][0] = dp[i & 1][j][1];
                }
            }
        }
        long res =  max(dp[l1 & 1][l2][0], dp[l1 & 1][l2][1]);
        return res % mod_p;
    }
};

int main() {
    vector<int> nums1 = {2,4,5,8,10};
    vector<int> nums2 = {4,6,8,9};
    Solution s;
    s.maxSum(nums1, nums2);
}