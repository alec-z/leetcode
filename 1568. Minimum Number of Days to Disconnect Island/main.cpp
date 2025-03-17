#include <vector>
using namespace std;

class Solution {
    int m, n;
    vector<vector<int>> mark;
    vector<vector<int>> _grid;
public:
    int minDays(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int land = 0;
        int min_adj = 10;
        this->_grid = grid;
        mark.resize(m, vector<int> (n, 0));
        bool found = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (_grid[i][j] == 1) {
                    found = true;
                    bool res = count_island(i, j);
                    if (res) {
                        return 0;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        if (!found) {
            return 0;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (_grid[i][j] == 1) {
                    _grid[i][j] = 0;
                    if (count_island(i, j)) {
                        return 1;
                    }
                    _grid[i][j] = 1;
                }
            }
        }
        return 2;
    }
    bool count_island(int i, int j) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) 
                mark[i][j] = 0;
        bool found = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)  {
                if (_grid[i][j] == 1) {
                    if (!found) {
                        dfs(i, j);
                        found = true;
                    } else {
                        if (mark[i][j] == 0) {
                            return true;
                        }
                    }
                }
            }
        }
        if (!found) {
            return true;
        } else {
            return false;
        }
    }
    void dfs(int i, int j) {
        mark[i][j] = 1;
        if (i - 1 >=0 && _grid[i - 1][j] == 1 && mark[i - 1][j] == 0) {
            dfs(i - 1, j);
        }
        if (j + 1 < n && _grid[i][j + 1] == 1 && mark[i][j + 1] == 0) {
            dfs(i, j + 1);
        }
        if (i + 1 < m && _grid[i + 1][j] == 1 && mark[i + 1][j] == 0) {
            dfs(i + 1, j);
        }
        if (j -1 >= 0 && _grid[i][j - 1] == 1 && mark[i][j - 1] == 0) {
            dfs(i, j - 1);
        }
    }
};