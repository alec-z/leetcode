#include <utility>
#include <vector>
using namespace std;
#include <map>
class TreeAncestor {
    int n;
    vector<int>& parent;
    map<pair<int,int>, int> h_m;
public:
    TreeAncestor(int n, vector<int>& parent): n(n), parent(parent) {
    }
    int getKthAncestor(int node, int k) {
        if (node == -1) {
            return -1;
        }
        if (k == 0) {
            return node;
        }
        if (k > 8) {
            auto p = h_m.upper_bound(make_pair(node, k));
            int res = -1;
            if (p != h_m.begin()) {
                p--;
                if (p->first.first == node) {
                    if (p->first.second == k) {
                        return p->second;
                    } else {
                        res =  getKthAncestor(p->second, k-p->first.second);
                        h_m[make_pair(node, k)] = res;
                        return res;
                    }
                }
            }
            res = getKthAncestor(parent[node], k - 1);
            h_m[make_pair(node, k)] = res;
            return res;
        } else {
            return getKthAncestor(parent[node], k - 1);
        }
    }
};

