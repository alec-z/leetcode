#include <string>
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
    
public:
    using ll = unsigned long long;
    ll qpow(ll a, ll b) {
        ll res = 1;
        for (;b > 0; b >>= 1) {
            if (b & 1) {
                res *= a;
            }
            if (a <= 1e9)
                a *= a;
            else
                return res;
        }
        return res;
    }
    string smallestGoodBase(string n) {
        long long target = std::stoll(n);
        ll x_min = target - 1;
        for (ll n = 2; n <= 62; n++) {
            ll x_l = std::max(2ull, (ll)(floor(std::powl(target + 1, 1.0 / n))));
            ll x_h = (ll)(ceil(std::pow(target, 1.0 / (n - 1)))) + 1;
            ll x_m;
            while (x_l < x_h) {
                x_m = (x_l + x_h) / 2;
                ll t = qpow(x_m, n) - 1;
                if (target * (x_m - 1) > t) {
                    x_l = x_m + 1;
                } else if (target * (x_m - 1)  < t ) {
                    x_h = x_m;
                } else {
                    break;
                }
            }
            if (x_l < x_h && x_m < x_min) {
                x_min = x_m;
            }
        }
        return std::to_string(x_min);
    }
};
int  main() {
    Solution s;
    cout << s.smallestGoodBase("470988884881403701") << endl;

}