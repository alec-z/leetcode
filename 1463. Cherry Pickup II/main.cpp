#include <limits>
#include <vector>
using namespace std;
class Solution {
  public:
    int cherryPickup(vector<vector<int>> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MIN_INT = numeric_limits<int>::min();
        vector<vector<vector<int>>> res(
            2, vector<vector<int>>(n, vector<int>(n, MIN_INT)));
        res[0][0][n - 1] = grid[0][0] + grid[0][n - 1];
        for (int l = 0; l < m - 1; l++) {
            for (int i = 0; i < min(n,l+1); i++) {
                for (int j = max(i + 1, n - 1 - l); j < n; j++) {
                    for (int ik = -1; ik <= 1; ik++) {
                        for (int jk = -1; jk <= 1; jk++) {
                            int new_i = i + ik;
                            int new_j = j + jk;
                            if (i + ik < j + jk && i + ik >= 0 &&
                                j + jk <= n - 1) {
                                res[(l + 1) & 1][new_i][new_j] =
                                    max(res[(l + 1) & 1][new_i][new_j],
                                        res[l & 1][i][j] + grid[l + 1][new_i] +
                                            grid[l + 1][new_j]);
                            }
                        }
                    }
                }
            }
        }
        int max_v = MIN_INT;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                max_v = max(max_v, res[(m - 1) & 1][i][j]);
            }
        }
        return max_v;
    }
};