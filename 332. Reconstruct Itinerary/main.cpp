#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;
class Digraph {
    public:
    Digraph(vector<vector<string>>& tickets) {
        for (auto& ticket: tickets) {
            put(ticket[0], ticket[1]);
        }
    }
    map<string, int> vers_stoi;
    vector<string> vers_itos;
    vector<vector<int>> adj;
    int edges_len = 0;
    void put(const string& v, const string& w) {
        if (vers_stoi.find(v) == vers_stoi.end()) {
            vers_itos.push_back(v);
            adj.push_back({});
            vers_stoi[v] =  vers_itos.size() - 1;
        }
        int v_id = vers_stoi[v];

        if (vers_stoi.find(w) == vers_stoi.end()) {
            vers_itos.push_back(w);
            adj.push_back({});
            vers_stoi[w] =  vers_itos.size() - 1;
        }
        int w_id = vers_stoi[w];
        adj[v_id].push_back(w_id);
    };

    vector<int>& adj_out(int v) {
        return adj[v];
    }

    int vert_size() const {
        return vers_itos.size();
    }
};

class Traverse {
    int starter = -1;
    Digraph & digraph;
    vector<string> res;
    public:
    Traverse(Digraph &di): digraph(di) {
        for (int i = 0; i < digraph.vert_size(); i++) {
            if (digraph.vers_itos[i] == "JFK") {
                starter = i;
                break;
            }
        }
    }

    void dfs(int v) {
        vector<int> & adjs = digraph.adj_out(v);
        
        while (!adjs.empty()) {
            string min_code = "";
            int next = -1;
            for (int i = 0; i < adjs.size(); i++) {
                int w = adjs[i];
                if (min_code == "" || min_code > digraph.vers_itos[w]) {
                    min_code = digraph.vers_itos[w];
                    next = i;
                }
            }
            int next_v = adjs[next];
            adjs.erase(adjs.begin() + next);
            dfs(next_v);
        }
        res.push_back(digraph.vers_itos[v]);
    }

    vector<string> itinerary() {
        dfs(starter);
        reverse(res.begin(), res.end());
        return res;
    }
};


class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        Digraph di(tickets);
        Traverse trav(di);
        return trav.itinerary();
    }
};

int main() {
    vector<vector<string>> tickets {
        {"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}
    };
    vector<vector<string>> tickets2 {
        {"JFK","SFO"},
        {"JFK","ATL"},
        {"SFO","ATL"},
        {"ATL","JFK"},
        {"ATL","SFO"}
    };
    Solution s;
    for (auto n: s.findItinerary(tickets)) {
        cout << n << endl;

    }
}