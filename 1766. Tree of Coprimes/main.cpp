#include <vector>
#include <functional>

using namespace std;

const int max_num = 50;
class Solution {
    private:
        int gcd(int a, int b) {
            if (a < b) {
                return _gcd(b, a);
            } else {
                return _gcd(a, b);
            }
        }
        int _gcd(int a, int b) {
            if (b==0) return a;
            return _gcd(b, a % b);
        }
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int len = nums.size();
        vector<int> path(max_num + 1, -1);
        vector<vector<int>> g(len + 1);
        for (auto & e: edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<int> res(len, -1);
        vector<int> l_to_e(len, -1);
        function<void(int, int, int)> dfs = [&](int root, int p_root, int level)->void {
            int value = nums[root];
            int max_top = -1;
            for (int ancestor = 1; ancestor <= max_num; ancestor++) {
                if (path[ancestor] != -1) {
                    if (gcd(value, ancestor) == 1) {
                        max_top = max(max_top, path[ancestor]);
                    }
                }
            }
            l_to_e[level] = root;
            res[root] = (max_top == -1) ? -1: l_to_e[max_top];
            
            int old_path = path[value];
            path[value] = level;
            for (auto c: g[root]) {
                if (c != p_root) {
                    dfs(c, root, level + 1);
                }
            }
            path[value] = old_path;
        };
        dfs(0, -1, 0);
        return res;
    }
};

int main() {
    vector<int> input = {9,16,30,23,33,35,9,47,39,46,16,38,5,49,21,44,17,1,6,37,49,15,23,46,38,9,27,3,24,1,14,17,12,23,43,38,12,4,8,17,11,18,26,22,49,14,9};
    vector<vector<int>> edges = {{17,0},{30,17},{41,30},{10,30},{13,10},{7,13},{6,7},{45,10},{2,10},{14,2},{40,14},{28,40},{29,40},{8,29},{15,29},{26,15},{23,40},{19,23},{34,19},{18,23},{42,18},{5,42},{32,5},{16,32},{35,14},{25,35},{43,25},{3,43},{36,25},{38,36},{27,38},{24,36},{31,24},{11,31},{39,24},{12,39},{20,12},{22,12},{21,39},{1,21},{33,1},{37,1},{44,37},{9,44},{46,2},{4,46}};
    Solution s;
    
    s.getCoprimes(input, edges);
}

