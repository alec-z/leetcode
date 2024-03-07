#include <iostream>
#include <vector>
#include <limits>

using namespace std;



class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n =matrix[0].size();
        vector<vector<int>> sums_00(m);
        for (int i = 0; i < m; i++) sums_00[i].resize(n, 0);
        int i_1, j_1, i_j_1;
        int max = numeric_limits<int>::min();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int i_1 = 0, j_1 = 0, i_j_1 = 0;
                if (i > 0) i_1 = sums_00[i - 1][j];
                if (j > 0) j_1 = sums_00[i][j - 1];
                if (i > 0 && j > 0) i_j_1 = sums_00[i - 1][j - 1];
                sums_00[i][j] = i_1 + j_1 + matrix[i][j] - i_j_1;
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int x = i; x < m; x++) {
                    for (int y = j; y < n; y ++) {
                        int i_1 = 0, j_1 = 0, i_j_1 = 0, s;
                        if (i > 0) i_1 = sums_00[i - 1][y];
                        if (j > 0) j_1 = sums_00[x][j - 1];
                        if (i > 0 && j > 0) i_j_1 = sums_00[i - 1][j - 1];
                        s = sums_00[x][y] - i_1 - j_1 + i_j_1;
                        if (s > max && s <= k) {
                            max = s;
                        }
                    }
                }
            }
        }
        return max;
    }
};

int main() {
    vector<vector<int>> matrix {
        {1,0,1},{0,-2,3}
    };
    Solution s;
    cout << s.maxSumSubmatrix(matrix, 2) << endl;
}