#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        int l = cuboids.size();
        auto larger = [&](int d_p, int d_d, int u_p, int u_d) -> bool {
            if (d_p == u_p) return false;
            const auto & d = cuboids[d_p];
            const auto & u = cuboids[u_p];
            if (d[d_d] >= u[u_d]) {
                int d_0 = d[0], d_1 = d[1], u_0 = u[0], u_1 = u[1];
                switch (d_d) {
                    case 0:
                        d_0 = d[2];
                        break;
                    case 1:
                        d_1 = d[2];
                        break;
                }
                switch (u_d) {
                    case 0:
                        u_0 = u[2];
                        break;
                    case 1:
                        u_1 = u[2];
                        break;
                }
                if (d_0 > d_1) swap(d_0, d_1);
                if (u_0 > u_1) swap(u_0, u_1);
                if (d[d_d] == u[u_d] && d_0 == u_0 && d_1 ==u_1) {
                    return d_p > u_p;
                }
                return d_0 >= u_0 && d_1 >=u_1;
            }
            else {
                return false;
            }
        };
        vector<vector<int>> dp(l, vector<int>(3, 0));
        int res = 0;
        function<int(int, int)> try_f = [&](int p, int d) -> int {
            if (dp[p][d] > 0) return dp[p][d];
            int ans = 0;
            const auto & cur = cuboids[p];
            for (int i = 0; i < l; i++) {
                if (i == p) continue;
                for (int ud = 0; ud < 3; ud++) {
                    if (larger(p, d, i, ud)) {
                        ans = max(ans, try_f(i, ud));
                    }
                }
            }
            ans += cuboids[p][d];
            res = max(res, ans);
            return (dp[p][d] = ans);

        };
        
        for (int i = 0; i < l; i++) {
            for (int u = 0; u < 3; u++) {
                res  = max(res, try_f(i, u));
            }
        }
        return res;
    }
};