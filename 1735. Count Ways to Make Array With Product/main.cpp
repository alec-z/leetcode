#include <utility>
#include <vector>
#include <map>
#include <functional>
using namespace std;
const unsigned mod_p = 1e9 + 7;
class Solution {
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        unsigned len = queries.size();
        vector<int> res(len, 0);
        map<pair<int,int>, unsigned> dp;
        function<unsigned(int, int)> try_f = [&](int n, int k) -> unsigned {
            if (n == 1) {
                return 1;
            }
            if (k == 1) {
                return 1;
            }
            auto p = dp.find(make_pair(n, k));
            if (p != dp.end()) {
                return p->second;
            }
            unsigned long long r = 0;
            unsigned sqrt_n = sqrt(k);
            if (n % 2 == 0) {
                for (unsigned d = 1; d <= sqrt_n; d++) {
                    if (k % d == 0) {
                        unsigned long long first = try_f(n / 2, d);
                        unsigned long long last = try_f(n / 2, k / d);
                        unsigned long long all = (first * last) % mod_p;
                        if (d * d != k) {
                            all = (all + all) % mod_p; 
                        }
                        r += all;
                        r %= mod_p;
                    }
                }
            } else {
                for (unsigned d = 1; d <= k; d++) {
                    if (k % d == 0) {
                        unsigned long long first = try_f(n - 1, k / d);
                        r += first;
                        r %= mod_p;
                    }
                }
            }
            return (dp[make_pair(n, k)] = r);
        };

        for (int i = 0; i < len; i++) {
            int n = queries[i][0];
            int k = queries[i][1];
            res[i] = try_f(n, k);
        }
        return std::move(res);
    }
};

int main() {
    vector<vector<int>> queries = {{73,660}};
    Solution s;
    s.waysToFillArray(queries);

}