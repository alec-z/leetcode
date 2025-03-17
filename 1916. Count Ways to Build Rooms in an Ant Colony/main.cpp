#include <vector>
#include <iostream>
#include <functional>
using namespace std;
const long long MOD_P = 1e9+7;
class Solution {
public:
    using ll = long long;
    static long long qPow(long long a, long long b) {
        long long res = 1, w = a;
        for (; b ; b >>= 1, w = (w * w) % MOD_P) {
            if (b & 1) res = (res * w) % MOD_P;
        }
        return res;
    }
    static long long s_combin(vector<ll> & fac, vector<ll> & ifac, int n, int m) {
        return (fac[n] * ifac[m] % MOD_P) * ifac[n-m] % MOD_P;
    }
public:
    int waysToBuildRooms(vector<int>& prevRoom) {
        int n = prevRoom.size();
        vector<vector<int>> tree(n);
        vector<int> nums(n, 0);
        for (int i = prevRoom.size() - 1; i >= 0; i--) {
            int p = prevRoom[i];
            if (p != -1) {
                tree[p].push_back(i);
            }
        }
        function<long(long)> try_n = [&](long root) -> long {
            if (nums[root] > 0) return nums[root];
            auto & children = tree[root];
            long res = 1;
            for (auto c: children) {
                res += try_n(c);
            }
            return (nums[root] = res);
        };

        try_n(0);
        
        vector<ll> fac(n + 1, 1);
        vector<ll> ifac(n + 1, 1);
        for (int i = 2; i <= n; i++) {
            fac[i] = (fac[i - 1] * i) % MOD_P;

            ifac[i] = qPow(fac[i], MOD_P - 2);
        }
        function<long(long)> try_f = [&](long root) -> long {
            auto & children = tree[root];
            long res = 1;
            long n = 0;
            for (auto c: children) {
                res = ((res * try_f(c) % MOD_P) * s_combin(fac, ifac, nums[c] + n, n)) % MOD_P;
                n += nums[c];
            }
            return (res);

        };
        return try_f(0);
    }
};

int main() {
    Solution s; 
    vector<int> prevRoom = {-1,0,0,1,2};
    cout << s.waysToBuildRooms(prevRoom) << endl;
}