#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> t_water;
    vector<vector<int>> height_map;
    int m;
    int n;
    void try_w(int i, int j) {
        int min_height = t_water[i][j] + height_map[i][j];
        if (i - 1 >= 0) min_height = min(min_height, t_water[i - 1][j] + height_map[i - 1][j]);
        if (j - 1 >= 0) min_height = min(min_height, t_water[i][j - 1] + height_map[i][j - 1]);
        if (i + 1 < m) min_height = min(min_height, t_water[i + 1][j] + height_map[i + 1][j]);
        if (j + 1 < n) min_height = min(min_height, t_water[i][j + 1]  + height_map[i][j + 1]);
        int new_water = max(0, min_height - height_map[i][j]);
        if (new_water < t_water[i][j]) {
            t_water[i][j] = new_water;
            if (i - 1 >= 0)  try_w(i - 1, j);
            if (j - 1 >= 0) try_w(i,j - 1);
            if (i + 1 < m)  try_w(i + 1, j);
            if (j + 1 < n)  try_w(i,j + 1);
        }
    }
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        m = heightMap.size();
        n = heightMap[0].size();
        t_water.resize(m, vector<int>(n, 1e5));
        height_map = heightMap;
        for (int j = 0; j < n; j++) {
            t_water[0][j] = 0;
            t_water[m - 1][j] = 0;
        }
        for (int i = 0; i < m; i++) {
            t_water[i][0] = 0;
            t_water[i][n - 1] = 0;
        }
        int all = 0;
        for (int i = 1; i < m -1; i++) {
            for (int j = 1; j < n - 1; j++) {
                try_w(i,j);
            }
        }
        for (int i = 1; i < m -1; i++) {
            for (int j = 1; j < n - 1; j++) {
                all += t_water[i][j];
            }
        }
        return all;
    }
};

int main() {
    Solution s;
    vector<vector<int>> heightMap = {{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
    s.trapRainWater(heightMap);

}