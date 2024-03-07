#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), [](const vector<int> & e1, const vector<int> & e2){return e1[1] < e2[1];});
        int len = envelopes.size();
        auto compare = [](const pair<int,int> & a, const pair<int, int> &b) {
            return a.first > b.first || (a.first == b.first && a.second > b.second);
        };
        set<pair<int,int>, decltype(compare)> tree_set(compare);
        vector<pair<int, int>> same_height;
        same_height.push_back(make_pair(1, envelopes[0][0]));
        int height = envelopes[0][1], max_doll = 1;
        
        for (int i = 1; i < len; i++) {
            const vector<int> & e = envelopes[i];
            if (e[1] != height) {
                while (!same_height.empty()) {
                    tree_set.insert(same_height.back());
                    same_height.pop_back();
                } 
                height = e[1];                
            }
            auto p = tree_set.upper_bound(make_pair(max_doll, e[0]));
            int doll = 1;
            while (p != tree_set.end()) {
                if ((*p).second >= e[0]) {
                    p = tree_set.upper_bound(make_pair((*p).first, e[0]));
                } else {
                    doll = (*p).first + 1;
                    break;
                }
            }
            same_height.push_back(make_pair(doll, e[0]));
            if (doll > max_doll) {
                max_doll = doll;
            }
        }

        return max_doll;
    }
};