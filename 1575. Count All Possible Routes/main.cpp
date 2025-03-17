#include <vector>
using namespace std;
const long mod_p = 1e9 + 7;
class Solution {
  public:
    int countRoutes(vector<int> &locations, int start, int finish, int fuel) {
        long l = locations.size();
        long dp[2][201][201] = {0};
        long max_fuel[2][201];
        for (long i = 0; i < l; i++) {
            max_fuel[0][i] = 0;
            for (long f = 0; f <= fuel; f++) {
                dp[0][i][f] = 0;
            }
        }
        long res = 0;
        dp[0][start][fuel] = 1;
        max_fuel[0][start] = fuel;
        if (start == finish) {
            res = 1;
        }
        for (long s = 1; true; s++) {
            for (long i = 0; i < l; i++) {
                max_fuel[s & 1][i] = 0;
                for (long f = 0; f <= fuel; f++) {
                    dp[s & 1][i][f] = 0;
                }
            }
            bool found = false;
            for (long i = 0; i < l; i++) {
                for (long f = 1; f <= max_fuel[(s-1) & 1][i]; f++) {
                    if (dp[(s - 1) & 1][i][f] > 0) {
                        for (long t = 0; t < l; t++) {
                            if (t == i) continue;
                            long used = abs(locations[t] - locations[i]);
                            if (used <= f) {
                                found = true;
                                max_fuel[s & 1][t] = max(max_fuel[s & 1][t], f - used);
                                dp[s & 1][t][f - used] += dp[(s - 1) & 1][i][f];
                                dp[s & 1][t][f - used] %= mod_p;
                                if (t == finish) {
                                    res += dp[(s - 1) & 1][i][f];
                                    res %= mod_p;
                                }
                            }
                        }
                    }
                }
            }
            if (!found) {
                return res;
            }
        }
        return res;
    }
};