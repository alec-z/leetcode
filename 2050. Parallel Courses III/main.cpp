#include <vector>
#include <limits>
#include <stack>
using namespace std;
const int MAX_INT = numeric_limits<int>::max();
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<int> pre_nums(n + 1, 0);
        vector<int> finished(n + 1, 0);
        vector<vector<int>> g(n + 1);
        for (auto & r: relations) {
            pre_nums[r[1]]++ ;
            g[r[0]].push_back(r[1]);
        }

        stack<int, vector<int>> current;
        stack<int, vector<int>> next;
        for (int i = 1; i <= n; i++) {
            if (pre_nums[i] == 0) {
                finished[i] = time[i - 1];
                current.push(i);
            }
        }
        int res = 0;
        while (!current.empty()) {
            int c = current.front();
            current.pop();
            res = max(res, finished[c]);
            for (auto n: g[c]) {
                pre_nums[n]--;
                finished[n] = max(finished[n], finished[c] + time[n - 1]);
                if (pre_nums[n] == 0) {
                    current.push(n);
                }
            }
        }
        return res;
    }
};
