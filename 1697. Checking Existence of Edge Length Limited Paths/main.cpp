#include <utility>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>
using namespace std;
const int MAX_INT = numeric_limits<int>::max(); 
class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        vector<vector<pair<int, int> > > adj(n);
        map<pair<int, int>,  int> edges;

        for (auto & e: edgeList) {
            if (e[0] == e[1]) continue;
            if (e[0] > e[1]) swap(e[0], e[1]);
            auto pair = make_pair(e[0], e[1]);
            auto p = edges.find(pair);
            if (p == edges.end()) {
                edges[pair] = e[2];
            } else if (p->second > e[2]){
                edges[pair] = e[2];
            }
        }


        for (auto & e: edges) {
            adj[e.first.first].emplace_back(make_pair(e.first.second, e.second));
            adj[e.first.second].emplace_back(make_pair(e.first.first, e.second));
        }
       


        vector<int> visited(n, -1);
        function<bool(int, int, int, int)> dfs = [&](int s, int t, int l, int q_id) -> bool {
            visited[s] = q_id;
            if (s == t) return true;
            for (auto &e : adj[s]) {
                if (e.second < l && visited[e.first] != q_id) {
                    if (dfs(e.first, t, l, q_id)) return true;
                }
            }
            return false;
        };

        vector<bool> res(queries.size(), false);
        for (int i = 0; i < queries.size(); i++) {
            auto const & q = queries[i];
            res[i] = dfs(q[0], q[1], q[2], i);
        }
        return std::move(res);
    }
};

int main() {
    Solution s;
    int n = 3;
    vector<vector<int>> edgeList = {
        {0,1,2},{1,2,4},{2,0,8},{1,0,16}
    };
    vector<vector<int>> queries = {
        {{0,1,2},{0,2,5}}
    };
    s.distanceLimitedPathsExist(n, edgeList, queries);
}