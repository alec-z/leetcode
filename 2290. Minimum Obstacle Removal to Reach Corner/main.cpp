#include <vector>
#include <queue>
#include <functional>
#include <set>
#include <limits>
using namespace std;
using Point = pair<int, int>;
using PII = pair<int, Point>;
const int MAX_INT = numeric_limits<int>::max();
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, MAX_INT));
        dist[0][0] = 0;
        set<PII> pq;
        pq.insert({0, {0,0}});

        auto updateDist = [&](int u_m, int u_n, int m, int n) {
            int d = grid[m][n] == 1 ? 1 : 0;
            if (dist[u_m][u_n] + d < dist[m][n]) {
                if (dist[m][n] < MAX_INT)
                    pq.erase(pq.find({dist[m][n], {m, n}}));
                dist[m][n] = dist[u_m][u_n] + d;
                pq.insert({dist[m][n], {m, n}});
            }

        };
        while (!pq.empty()) {
            auto p = pq.begin()->second;
            auto d = pq.begin()-> first;
            if (p.first == m - 1 && p.second == n -1) return d;
            pq.erase(pq.begin());
            if (p.first > 0) {
                updateDist(p.first, p.second,  p.first - 1, p.second);
            }

            if (p.first < m -1) {
                updateDist(p.first, p.second,  p.first + 1, p.second);
            }

            if (p.second > 0) {
                updateDist(p.first, p.second,  p.first, p.second - 1);
            }

            if (p.second < n - 1) {
                updateDist(p.first, p.second,  p.first, p.second + 1);
            }
        }
        return 0; 
    }
};