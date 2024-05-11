#include <limits>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;
struct Point {
    int time;
    int r;
    int l;
};
const int MAX_INT = numeric_limits<int>::max();
auto comp = [](const Point &p1, const Point &p2) { return p1.time > p2.time; };

class Solution {
  public:
    int swimInWater(vector<vector<int>> &grid) {
        SubSolution subS(grid);
        return subS.swimInWater();
    }

    class SubSolution {
        vector<vector<int>> distances;
        int m;
        int n;
        priority_queue<Point, vector<Point>, decltype(comp)> wait_to_explore;
        vector<vector<int>> &grid;
        void dfs(int r, int l, int time) {
            if (r < 0 || r > m - 1 || l < 0 || l > n - 1) return;
            if (distances[r][l] == MAX_INT) {
                if (grid[r][l] <= time) {
                    distances[r][l] = time;
                    dfs(r - 1, l, time);
                    dfs(r, l + 1, time);
                    dfs(r + 1, l, time);
                    dfs(r, l - 1, time);
                } else {
                    wait_to_explore.push({grid[r][l], r, l});
                }
            }
        }

      public:
        SubSolution(vector<vector<int>> &grid) : grid(grid), wait_to_explore(comp) {
            m = grid.size();
            n = grid[0].size();
            distances.resize(m);
            for (int i = 0; i < m; i++) {
                distances[i].resize(n, MAX_INT);
            }
        }
        int swimInWater() {
            wait_to_explore.push({grid[0][0], 0, 0});
            while (!wait_to_explore.empty()) {
                auto p = wait_to_explore.top();
                wait_to_explore.pop();
                int time = p.time;
                dfs(p.r, p.l, p.time);
                if (distances[m - 1][n - 1] < MAX_INT) {
                    return time;
                }
            }
            return MAX_INT;
        }
    };
};

int main() {
    Solution s;
    vector<vector<int>> grid = {
        {0,2},{1,3}
    };
    cout << s.swimInWater(grid) << endl;
}