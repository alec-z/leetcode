#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
  public:
    int minCost(vector<int> &houses, vector<vector<int> > &cost, int m, int n,
                int target) {
        vector<vector<vector<int> > > f(m, vector<vector<int> > (n + 1 , vector<int>(target + 2)));
        const int MAX_INT = numeric_limits<int>::max();
        for (int i = 0; i < m; i++) {
            for (int c = 0; c <= n; c++) {
                for (int t = 0; t <= target + 1; t++) {
                    f[i][c][t] = MAX_INT;
                }
            }
        }

        if (houses[0] == 0) {
            for (int c = 1; c <= n; c++) {
                f[0][c][1] = cost[0][c - 1];
            }
        } else {
            f[0][houses[0]][1] = 0;
        }

        for (int i = 0; i < m - 1; i++) {
            for (int c = 1; c <= n; c++) {
                for (int t = 1; t <= min(target, i + 1); t++) {
                    if (f[i][c][t] == MAX_INT)
                        continue;
                    if (houses[i + 1] == 0) {
                        for (int nc = 1; nc <= n; nc++) {
                            if (nc == c) 
                                f[i + 1][nc][t] = min(f[i + 1][nc][t], f[i][c][t] + cost[i+1][nc - 1]);
                            else
                                f[i + 1][nc][t + 1] = min(f[i + 1][nc][t + 1], f[i][c][t] + cost[i + 1][nc - 1]);
                        }
                    } else {
                        if (houses[i + 1] == c) {
                            f[i+1][c][t] = min(f[i+1][c][t], f[i][c][t]);
                        } else {
                            f[i+1][houses[i + 1]][t + 1] = min(f[i+1][houses[i + 1]][t + 1], f[i][c][t]);
                        }
                    }
                }
            }
        }

        int res = MAX_INT;
        for (int c = 1; c <= n; c++) {
            res = min(res, f[m - 1][c][target]);
        }
        return res == MAX_INT ? -1 : res;
    }
};
int main() {
    Solution s;
    vector<int> houses = {0,0,0,0,0};
    vector<vector<int> > cost  = {{1,10},{10,1},{10,1},{1,10},{5,1}};
    s.minCost(houses, cost, 5, 2, 3);


    return 5;
}