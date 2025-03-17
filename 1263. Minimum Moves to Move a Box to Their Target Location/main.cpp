#include <vector>
#include <functional>
using namespace std;

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(4, false)));

        vector<vector<bool>> marked(m, vector<bool> (n, false));

        function<bool(int, int)> validate = [&](int i, int j) -> bool {
            return !marked[i][j] && grid[i][j] != '#' && grid[i][j] != 'B';
        };

        function<void(void)> clear_marked = [&]() -> void {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    marked[i][j] = false;
                }
            }
        };

        function<bool(int, int, int, int)> dfs = [&](int si, int sj, int ti, int tj) -> bool {
            marked[si][sj] = true;
            if (si == ti && sj == tj) return true;
            if (si - 1 >= 0) {
                if (validate(si - 1, sj)) return dfs(si - 1, sj, ti, tj);
            }

            if (sj + 1 < n) {
                if (validate(si, sj + 1)) return dfs(si, sj + 1, ti, tj);
            }

            if (si + 1 < m) {
                if (validate(si + 1, sj)) return dfs(si + 1, sj, ti, tj);
            }

            if (sj - 1 >= 0) {
                if (validate(si, sj - 1)) return dfs(si, sj - 1, ti, tj);
            }
            return false;
        };

        int bi, bj = 0;

        function<int(int, int, int)> try_f = [&](int si, int sj, int p) -> int {
            if (visited[si][sj][p]) return -1;
            visited[si][sj][p] = true;
            if (si == bi && sj == bi) return 0;
            switch(p) {
                case 0:
                    if (si + 1 < m && grid[si + 1][sj]) {
                        return 1 + try_f(si + 1, sj, 0);
                    }
                    break;
                case 1:
                    if (sj - 1 >= 0 && grid[si][sj - 1]) {
                        return 1 + try_f(si, sj - 1, 1);
                    }
                    break;

                case 2:
                    if (si + 1 < m && grid[si + 1][sj]) {
                        return 1 + try_f(si + 1, sj, 0);
                    }
                    break;

                case 3:
                    if (si + 1 < m && grid[si + 1][sj]) {
                        return 1 + try_f(si + 1, sj, 0);
                    }
                    break;
            }
            return false;
        };





    }
};