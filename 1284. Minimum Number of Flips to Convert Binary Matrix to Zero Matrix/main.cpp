#include <vector>
using namespace std;

class Solution {
    int m;
    int n;
    int min_steps;
    void flip(vector<vector<int>>& cur_mat, int y, int x) {
        cur_mat[y][x] = !cur_mat[y][x];
        if (y - 1 >= 0) cur_mat[y - 1][x] = !cur_mat[y - 1][x];
        if (x + 1 < n) cur_mat[y][x + 1] = !cur_mat[y][x + 1];
        if (y + 1 < m) cur_mat[y + 1][x] = !cur_mat[y + 1][x];
        if (x - 1 >= 0) cur_mat[y][x - 1] = !cur_mat[y][x - 1];
    }
    void backtrace(vector<vector<int>>& cur_mat, int pos, int steps) {
        bool all_zero = true;
        for (auto & arr : cur_mat)
            for (auto & num: arr)
                if (num == 1) {
                    all_zero = false;
                    goto breakLoop;
                }
        breakLoop: if (all_zero) {
            if (steps < min_steps) min_steps = steps;
            return;
        };
        for (; pos <= m * n - 1; pos++) {
            int y = pos / n;
            int x = pos % n;
            flip(cur_mat, y, x);
            backtrace(cur_mat, pos + 1, steps + 1);
            flip(cur_mat, y, x);
        }
    }
public:
    int minFlips(vector<vector<int>>& mat) {
        min_steps = 1e9;
        m = mat.size();
        n = mat[0].size();
        backtrace(mat, 0, 0);
        return min_steps == 1e9 ? -1: min_steps;
    }
};

int main() {
    Solution s;
    vector<vector<int>> mat {{0,0},{0,1}};
    s.minFlips(mat);
}