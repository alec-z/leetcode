#include <vector>
#include <set>
using namespace std;
class UnionFind {
    vector<vector<pair<int,int>>> sets;
    vector<vector<int>> set_nums;
    public:
        UnionFind(int m, int n):sets(m), set_nums(m) {
            for (int i = 0; i < m; i++) {
                sets[i].resize(n);
                set_nums[i].resize(n, 1);
                for (int j = 0; j < n; j++)
                    sets[i][j] = make_pair(i, j);
            }
        }
        pair<int, int> find(pair<int,int> x) {
            auto cur = x;
            auto p = sets[cur.first][cur.second];
            while (p != cur) {
                auto gp = sets[p.first][p.second];
                sets[cur.first][cur.second] = gp;
                cur = gp;
                p = sets[cur.first][cur.second];
            }
            return p;
        }
        int get_num(pair<int, int> x) {
            auto s = find(x);
            return set_nums[s.first][s.second];
        }
        pair<int, int> join(pair<int,int> x, pair<int,int> y) {
            auto s_x = find(x);
            auto s_y = find(y);
            if (s_x != s_y) {
                sets[s_y.first][s_y.second] = s_x;
                set_nums[s_x.first][s_x.second] += set_nums[s_y.first][s_y.second];
            }
            return s_x;
        }

};
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        UnionFind uf(m,n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                auto cur = make_pair(i, j);
                if (grid[i][j] == 1) {
                    if (j - 1 >= 0 && grid[i][j-1] == 1)
                        uf.join(cur, make_pair(i, j - 1));
                    if (i - 1 >= 0 && grid[i - 1][j] == 1)
                        uf.join(cur, make_pair(i - 1, j)); 
                }
            }
        }
        int max_i = 0;
        bool has_zero = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                auto cur = make_pair(i, j);
                int total = 0;
                if (grid[i][j] == 0) {
                    has_zero = true;
                    set<pair<int,int>> s_s;
                    if (i - 1 >= 0 && grid[i - 1][j] == 1) {
                        auto top_p = make_pair(i - 1, j);
                        auto top_s = uf.find(top_p);
                        if (s_s.find(top_s) == s_s.end()) {
                            total +=  uf.get_num(top_s);
                            s_s.insert(top_s);
                        }
                    }
                    if (j + 1 < n && grid[i][j + 1] == 1) {
                        auto right_s = uf.find(make_pair(i, j + 1));
                        if (s_s.find(right_s) == s_s.end()) {
                            total +=  uf.get_num(right_s);
                            s_s.insert(right_s);
                        }
                    }

                    if (i + 1 < m && grid[i + 1][j] == 1) {
                        auto bottom_s = uf.find(make_pair(i + 1, j));
                        if (s_s.find(bottom_s) == s_s.end()) {
                            total +=  uf.get_num(bottom_s);
                            s_s.insert(bottom_s);
                        }
                    }

                    if (j - 1 >= 0 && grid[i][j - 1] == 1) {
                        auto left_s = uf.find(make_pair(i, j - 1));
                        if (s_s.find(left_s) == s_s.end()) {
                            total +=  uf.get_num(left_s);
                            s_s.insert(left_s);
                        }
                    }
                }
                if (total + 1 > max_i) {
                    max_i = total + 1;
                }
            }
        }

        if (has_zero) {
            return max_i;
        } else {
            return m*n;
        }

    }
};
 