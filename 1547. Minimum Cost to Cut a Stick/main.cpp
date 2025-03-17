#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>
using namespace std;
const int MAX_INT = numeric_limits<int>::max();
class Solution {
    vector<int> n_cuts;
    int l_n;
    vector<vector<int>> dp_m;
public:
    int minCost(int n, vector<int>& cuts) {
        int l = cuts.size();
        n_cuts.resize(l+2, 0);
        n_cuts[0] = 0;
        n_cuts[1] = n;
        l_n = l+2;
        for (int i = 0; i < l; i++) n_cuts[i+2] = cuts[i];
        sort(n_cuts.begin(), n_cuts.end());
        dp_m.resize(l_n, vector<int> (l_n, -1));
        return min_try_f(0, l_n -1);
    }
    int min_try_f(int be, int en) {
        
        if (dp_m[be][en] != -1) {
            return dp_m[be][en];
        }
        if (en - be == 2) {
            int res = n_cuts[en] - n_cuts[be];
            dp_m[be][en] = res;
            return res;
        }
        if (en - be == 1) {
            dp_m[be][en] = 0;
            return 0;
        }
        int min_c = MAX_INT;
        for (int k = be + 1; k < en; k++) {
            min_c = min(min_c, min_try_f(be, k) + min_try_f(k, en));
        }
        min_c += n_cuts[en] - n_cuts[be];
        dp_m[be][en] = min_c;
        return min_c;
    }
};