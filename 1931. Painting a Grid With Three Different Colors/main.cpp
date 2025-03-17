#include <vector>
#include <functional>
#include <iostream>
using namespace std;
class Solution {
public:
    using ll = long long;
    const ll mod_p = 1e9 + 7;
    int colorTheGrid(int m, int n) {
        vector<vector<int>> components;
        int l = 0;
        int next = 0;
        vector<int> cur(m, 0);
        while (l >= 0) {
            if (l == m) {
                components.push_back((cur));
                l--;
                next = cur[l] + 1;
            }
            if (next == 3) {
                l--;
                if (l < 0) break;
                next = cur[l] + 1;
            } else {
                if (l == 0 || next != cur[l - 1]) {
                    cur[l] = next;
                    l++;
                    next = 0;
                } else {
                    next++;
                }
            }
        }

        function<bool(vector<int>& , vector<int>&)> compatible = [&](vector<int>& a, vector<int>& b) -> bool {
            for (int i = 0; i < m; i++) {
                if (a[i] == b[i]) return false;
            }
            return true;
        };

        int len = components.size();
        vector<vector<int>> compatibles(len, vector<int>());
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (i != j) {
                    if (compatible(components[i], components[j])) {
                        compatibles[i].push_back(j);
                    }
                }
            }
        }

        vector<vector<ll>> dp(2, vector<ll>(len, 0));
        for (int i = 0; i < len; i++) dp[0][i] = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < len; j ++) {
                dp[i & 1][j] = 0;
                for (auto pre: compatibles[j]) {
                    dp[i & 1][j] += dp[(i - 1) & 1][pre];
                    dp[i & 1][j] %= mod_p;
                }
            }
        }
        ll res = 0;
        for (auto s : dp[(n - 1) & 1]) {
            res += s;
            res %= mod_p;
        }
        return res;
    }
};

int main() {
    Solution s;
    int res = s.colorTheGrid(5, 5);
    cout << res <<endl;
}
