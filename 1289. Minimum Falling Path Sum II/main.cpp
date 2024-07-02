#include <vector>
#include <limits>
#include <iostream>
using namespace std;

const int MAX_INT = numeric_limits<int>::max();

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int min_val = MAX_INT;
        for (int i = 1; i <= m; i++) {
            min_val = MAX_INT;
            int second_min_val = MAX_INT;
            int min_val_p = -1;
            for (int j = 0; j < n; j++) {
                if (grid[i - 1][j] < min_val) {
                    min_val = grid[i - 1][j];
                    min_val_p = j;
                }
            }
            if (i == m) break;
            for (int j = 0; j < n; j++) {
                if (j != min_val_p && grid[i - 1][j] < second_min_val) {
                    second_min_val = grid[i - 1][j];
                }
            }
            
            for (int j = 0; j < n; j++) {
                if (j != min_val_p) {
                    grid[i][j] += min_val;
                } else {
                    grid[i][j] += second_min_val;
                }
            }
        }
        return min_val;
    }
};

int main() {
    vector<vector<int>> grid = {
        {1,2,3},{4,5,6},{7,8,9}
    };
    Solution s;
    cout << s.minFallingPathSum(grid);
}