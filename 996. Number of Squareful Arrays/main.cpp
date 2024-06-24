#include <vector>
#include <map>
#include <set>
#include <cmath>
using namespace std;
class Solution {
    vector<set<int>> adj;
    long total = 0;
    map<int, int> n_c;
    map<int, int> n_o;
    map<int, int> o_n;
    map<int, int> o_c;
    int len;
    int a_len;
    bool check(long x, long y) {
        double all = x + y;
        double s_all= sqrt(all);
        if (abs(round(s_all) - s_all) < 1e-9) {
            return true;
        } else {
            return false;
        }
    }

    void try_f(int pre, int level) {
        if (level == a_len - 1) {
            for (int i = 0; i < len; i++) {
                if (adj[pre].find(i) != adj[pre].end() && o_c[i] > 0) {
                    total++;
                }
            }
        } else {
            for (int i = 0; i < len; i++) {
                if ((level == 0 || (adj[pre].find(i)!=adj[pre].end())) && o_c[i] > 0) {
                    o_c[i]--;
                    try_f(i, level + 1);
                    o_c[i]++;
                }
            }
        }
    }
public:
    int numSquarefulPerms(vector<int>& nums) {
        a_len = nums.size();
        for (auto n : nums) {
            n_c[n]++;
        }
        int i = 0;
        for (auto p = n_c.begin(); p != n_c.end(); p++, i++) {
            n_o[p->first] = i;
        }
        for (auto p = n_o.begin(); p != n_o.end(); p++) {
            o_n[p->second] = p->first;
        }

        for (auto p = o_n.begin(); p != o_n.end(); p++) {
            o_c[p->first] = n_c[p->second];
        }
        len = o_n.size();
        adj.resize(len);
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (check(o_n[i], o_n[j])) {
                    adj[i].insert(j);
                }
            }
        }
        try_f(0, 0);
        return total;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,1,5, 3};
    s.numSquarefulPerms(nums);
}