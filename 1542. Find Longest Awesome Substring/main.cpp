#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();
        vector<vector<int> > dp(n+1, vector<int>(11, 0));
        for (int i = 0; i < n; i++) {
            dp[i][s[i] - '0'] = 1;
            dp[i][10] = 0;
        }
        for (int i = 1; i < n; i++) {
            int cur_n = s[i] - '0';
            int cur_n_l = dp[i - 1][cur_n];
            if (cur_n_l > 0)
                dp[i][10] = max(dp[i][10], cur_n_l + 1);
            else {
                dp[i][10] = max(dp[i][10], 0);
            }
            int l_10 = dp[i - 1][10];
            if (l_10 > 0 && i > l_10 && dp[i - 1- l_10][cur_n] > 0) {
                dp[i][10] = max(dp[i][10], dp[i - 1- l_10][cur_n] + l_10 + 1);
            }

            for (int k = 0; k <= 9; k++) {
                if (cur_n == k) {
                    dp[i][k] = max(dp[i][k], dp[i - 1][10] + 1);
                    int k_l = dp[i - 1][k];
                    if (k_l > 0 && i > k_l && dp[i - 1- k_l][cur_n] > 0) {
                        dp[i][k] = max(dp[i][k], dp[i - 1- k_l][cur_n] + k_l + 1);
                    }
                } else {
                    if (i > cur_n_l && cur_n_l > 0 && dp[i - 1 - cur_n_l][k] > 0) {
                        dp[i][k] = max(dp[i][k], dp[i - 1 - cur_n_l][k] + cur_n_l + 1);
                    }
                    int k_l = dp[i - 1][k];
                    if (i > k_l && k_l > 0 && dp[i - 1 - k_l][cur_n] > 0) {
                        dp[i][k] = max(dp[i][k], dp[i - 1 - k_l][cur_n] + k_l + 1);
                    }
                }
            }
        }
        int max_l = 0;
        for (int i = 0; i < n; i++) {
            for (int k = 0; k <= 10; k++) {
                max_l = max(max_l, dp[i][k]);
            }
        }
        return max_l;
    }
};
int main() {
    string str = "3242415";
    Solution s;
    cout << s.longestAwesome(str) << endl;
}