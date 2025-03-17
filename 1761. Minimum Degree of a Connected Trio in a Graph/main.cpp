#include <algorithm>
#include <vector>
#include <set>
using namespace std;
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n + 1);
        vector<int> degree(n + 1, 0);
        for (auto &e: edges) {
            if (e[0] < e[1]) {
                g[e[0]].push_back(e[1]);
            } else {
                g[e[1]].push_back(e[0]);
            }
            degree[e[0]]++;
            degree[e[1]]++;
        }

        for (auto &v:g){
            sort(v.begin(), v.end());
        }

        int res = 1e9;

        for (int n1 = 1; n1 <= n; n1++) {
            if (degree[n1] < 2 || degree[n1] - 2 >= res) continue; 
            for (auto p_n2 = g[n1].begin(); p_n2 != g[n1].end(); p_n2++) {
                int n2 = *p_n2;
                if (degree[n2] < 2 || degree[n1] + degree[n2] - 4 >= res) continue;
                for (auto p_i = p_n2, p_j = g[n2].begin(); p_i != g[n1].end() && p_j != g[n2].end();) {
                    if (*p_i == *p_j) {
                        res = min(res, degree[n1] + degree[n2] + degree[*p_i] - 6);
                        p_i++;
                        p_j++;
                    } else if (*p_i < *p_j) {
                        p_i++;
                    }
                    else {
                        p_j++;
                    }
                }
            }
        }
        if (res==1e9) res = -1;
        return res;
    }
};