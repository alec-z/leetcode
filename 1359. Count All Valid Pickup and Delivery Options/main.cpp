unsigned mod_p = 1e9 +7;

class Solution {
public:
    int countOrders(int n) {
        unsigned dp[2];
        dp[1] = 1;
        for (unsigned i = 2; i <= n; i++) {
            unsigned long long tmp = (unsigned long long)(i) * (2*i - 1);
            dp[i & 1] = (tmp * dp[(i - 1) & 1]) % mod_p;
        }
        return dp[n & 1];
    }
};