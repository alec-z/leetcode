#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
    int m;
    int n;
    int from_point_max_path(int position, vector<vector<int>> & paths, vector<vector<int>> & matrix) {
        int i = position / n;
        int j = position % n;
        int max_path = 1;
        int cur_val = matrix[i][j];
        if (i > 0 && matrix[i - 1][j] > cur_val) {
            max_path = max(max_path, paths[i - 1][j] + 1);
        }
        if (i < m - 1 && matrix[i + 1][j] > cur_val) {
            max_path = max(max_path, paths[i + 1][j] + 1);
        }
        if (j > 0 && matrix[i][j - 1] > cur_val) {
            max_path = max(max_path, paths[i][j - 1] + 1);
        }
        if (j < n - 1 && matrix[i][j + 1] > cur_val) {
            max_path = max(max_path, paths[i][j + 1] + 1);
        }
        paths[i][j] = max_path;
        return max_path;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        int max_path = 0;
        vector<pair<int, int>> nums;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                nums.push_back(make_pair(matrix[i][j], i * n + j));
            }
        }
        sort(nums.begin(), nums.end(), [](const pair<int, int> & a, const pair<int, int> & b) {
            return a.first < b.first;
        });

        vector<vector<int>> paths(m);
        for (int i = 0; i < m; i++) paths[i].resize(n, 0);
        for (int i = nums.size() - 1; i >= 0; i--) {
            max_path = max(max_path, from_point_max_path(nums[i].second, paths, matrix));
        }
        return max_path;
    }
};

int main() {
    vector<vector<int>> matrix {{1, 2}};
    Solution s;
    cout << s.longestIncreasingPath(matrix) << endl;
}