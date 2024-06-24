#include <vector>
using namespace std;

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> sums(m + 1);
        sums[0].resize(n + 1 , 0);
        int row_to_l = 0;
        for (int r = 1; r < m + 1; r ++) {
            sums[r].resize(n + 1, 0);
            row_to_l = 0;
            for (int l = 1; l < n + 1; l++) {
                row_to_l += matrix[r - 1][l - 1];
                sums[r][l] = sums[r - 1][l] + row_to_l;
            }
        }
        int result = 0;
        for (int r0 = 0; r0 < m; r0 ++) {
            for (int l0 = 0; l0 < n; l0++) {
                for (int r1 = r0; r1 < m; r1++) {
                    for (int l1 = l0; l1 < n; l1++) {
                        int sum = sums[r1 + 1][l1 + 1] - sums[r1 + 1][l0] - sums[r0][l1 + 1] + sums[r0][l0];
                        if (sum == target) {
                            result++;
                        }
                    }
                }
            }
        }
        return result;     
    }
};