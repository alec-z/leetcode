#include <vector>
#include <iostream>
using namespace std;

class Solution {
    int verts;
    vector<vector<bool>> visited;
    int m;
    int n;
    int visited_num;
    int res;
    void dfs(int r, int l,  vector<vector<int>> & m_grid) {
        if (visited[r][l] || m_grid[r][l] == -1) {
            return;
        }
        visited[r][l] = true;
        visited_num++;
        if (m_grid[r][l] == 2) {
            if (visited_num == verts){
                res++;
            }
        } else {
            if (visited_num < verts) {
                if (r < m -1)
                    dfs(r + 1, l, m_grid);
                if (r > 0)
                    dfs(r - 1, l, m_grid);
                if (l < n -1)
                    dfs(r, l+1, m_grid);
                if (l > 0)
                    dfs(r, l -1, m_grid);
            }
        }
        visited[r][l] = false;
        visited_num--;
    } 
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        verts = 0;
        res = 0;
        visited_num = 0;
        int start_r;
        int start_l;
        visited.resize(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != -1) {
                    verts++;
                } 
                if (grid[i][j] == 1) {
                    start_r = i;
                    start_l = j;
                }
            }
        }
        dfs(start_r, start_l, grid);
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
    cout << s.uniquePathsIII(grid);
    
}