#include <vector>
#include <limits>
using namespace std;

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        const int MAX_INT = numeric_limits<int>::max();
        vector<vector<int>> func(d + 1, vector<int>(n, MAX_INT));
        if (d > n) return -1;
        int max_i = -1;
        for (int i = 0; i < n; i++) {
            max_i = max(max_i, jobDifficulty[i]);
            func[1][i] = max_i;
        }
        for (int i = 1; i < d; i++) {
            for (int j = i - 1; j < n; j++) {
                int max_j_nj = -1;
                for (int nj = j + 1; nj < n; nj++) {
                    max_j_nj = max(max_j_nj,jobDifficulty[nj]);
                    func[i + 1][nj] = min(func[i+1][nj], func[i][j] + max_j_nj);
                }
            }
        }
        return func[d][n - 1];
    }
};