#include <set>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;


class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size();
        vector<int> next_pointers(k, 0);
        set<int> wait_move;
        set<pair<int, int>> range_tree;
        int min_range = numeric_limits<int>::max();
        int min_begin = numeric_limits<int>::max();
        for (int i = 0; i < k; i++) wait_move.insert(i);

        while (true) {
            for (auto wm_i: wait_move) {
                vector<int> & one_nums = nums[wm_i];
                int & next_p = next_pointers[wm_i];
                if (next_p == one_nums.size()) {
                    return vector<int> {min_begin, min_begin + min_range};
                }
                
                int next_p_v = one_nums[next_p];
                range_tree.insert(make_pair(next_p_v, wm_i));
                while (next_p < one_nums.size() && next_p_v == one_nums[next_p]) {
                    next_p++;
                }
            }
            wait_move.clear();
            auto p = range_tree.begin();
            int p_value = p->first;
            auto p_pre = p;
            int last_value = range_tree.rbegin()->first;
            if ((last_value - p_value) < min_range) {
                min_range = (last_value - p_value);
                min_begin = p_value;
            }

            while (p != range_tree.end() && p->first == p_value) {
                if (p_pre != p) range_tree.erase(p_pre);
                wait_move.insert(p->second);
                p_pre = p;
                p++;
            }
            range_tree.erase(p_pre);
        }
    }
};