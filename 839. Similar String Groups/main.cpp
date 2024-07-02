#include <string>
using namespace std;
class Solution {
    bool check_similar(string & a, string &b) {
        int res = 0;
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i]) {
                res++;
                if (res > 2) return false;
            }
        return res == 2;
    }
    int group;
    vector<vector<int>> graph;
    vector<int> marked;
    void dfs(int i) {
        if (marked[i] != 0) {
            return;
        }
        marked[i] = group;
        for (auto n: graph[i]) {
            dfs(n);
        }
    }
public:
    int numSimilarGroups(vector<string>& strs) {
        
        int n = strs.size();
        graph.resize(n, vector<int>());
        marked.resize(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (check_similar(strs[i], strs[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        group = 0;
        for (int i = 0; i < n; i++) {

            if (marked[i] == 0) {
                group++;
                dfs(i);
            }
        }
        return group;
    }
};