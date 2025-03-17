#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const long mod_p = 1e9 + 7;

class Solution {
  public:
    int countRoutes(vector<int> &locations, int start, int finish, int fuel) {
        int be_v = locations[start];
        int en_v = locations[finish];
        int l = locations.size();
        int n_start, n_finish;
        sort(locations.begin(), locations.end());
        for (int i = 0; i < l; i++) {
            if (locations[i] == be_v)
                n_start = i;
            if (locations[i] == en_v)
                n_finish = i;
        }

        unsigned int dp[201][201] = {0};
        dp[0][n_start] = 1; 

        for (int f = 1; f <= fuel; f++) {
            for (int en = 0; en < l; en++) {
                dp[f][en] = 0;           
                
                int p = en + 1;
                while (p < l && locations[p] - locations[en] <= f) {
                     dp[f][en] += dp[f - (locations[p] - locations[en])][p];
                     dp[f][en] %= mod_p;
                     p++;
                }
                p = en - 1;
                while (p >= 0 && locations[en] - locations[p]<= f) {
                     dp[f][en] += dp[f - (locations[en] - locations[p])][p];
                     dp[f][en] %= mod_p;
                     p--;
                }
               
            }
        }
        unsigned int res = 0;
        for (int i = 0; i <= fuel; i++) {
            res += dp[i][n_finish];
            res %= mod_p;
        }    
        return res;
    }
};
int main() {
    vector<int> loc = {4,3,1};
    int start = 1;
    int finish = 0;
    int fuel = 6;
    Solution s;
    cout << s.countRoutes(loc, start, finish, fuel) << endl;
}