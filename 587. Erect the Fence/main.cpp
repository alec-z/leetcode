#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        set<pair<int,int>> res;
        int min_x = 101;
        int max_x = -1;
        for (auto& tree: trees) {
            if (tree[0] < min_x) {
                min_x = tree[0];
            }
            if (tree[0] > max_x) {
                max_x = tree[0];
            }
        }

        for (auto& tree: trees) {
            if (tree[0] == min_x) {
                res.insert(make_pair(tree[0], tree[1]));
            }
        }
        auto cur_tree = *(res.begin());

        while (cur_tree.first < max_x) {
            double min_slop = 1e6;
            int min_x_diff = 101;
            pair<int,int> next_tree;
            for (auto& tree: trees) {
                if (tree[0] > cur_tree.first) {
                    int tmp_x_diff =  (tree[0] - cur_tree.first);
                    double tmp_slop =(double)(tree[1] - cur_tree.second) / tmp_x_diff;
                    if (tmp_slop < min_slop - 1e-9 || (tmp_slop < min_slop + 1e-9  && tmp_x_diff < min_x_diff)) {
                        min_slop = tmp_slop;
                        min_x_diff = tmp_x_diff;
                        next_tree = {tree[0], tree[1]};
                    }
                }
            }
            cur_tree = next_tree;
            res.insert(cur_tree);
        }

        int max_y = cur_tree.second;
        for (auto& tree: trees) {
            if (tree[0] == max_x) {
                res.insert({tree[0], tree[1]});
                if (tree[1] > max_y) {
                    max_y = tree[1];
                }
            }
        }
        cur_tree = {max_x, max_y};

        while (cur_tree.first > min_x) {
            double min_slop = 1e6;
            int min_x_diff = 101;
            pair<int,int> next_tree;
            for (auto& tree: trees) {
                if (tree[0] < cur_tree.first) {
                    int tmp_x_diff =  (tree[0] - cur_tree.first);
                    double tmp_slop =(double)(tree[1] - cur_tree.second) / tmp_x_diff;
                    if (tmp_slop < min_slop - 1e-9 || (tmp_slop < min_slop + 1e-9 && tmp_x_diff > min_x_diff)) {
                        min_slop = tmp_slop;
                        min_x_diff = tmp_x_diff;
                        next_tree = {tree[0], tree[1]};
                    }
                }
            }
            cur_tree = next_tree;
            res.insert(cur_tree);
        }
        vector<vector<int>> f_res;
        for (auto & tree: res) {
            f_res.push_back({tree.first, tree.second});
        }
        return f_res;

    }
};

int main() {
    vector<vector<int>> tree {
        {1,1},
        {2,2},{2,0}
        ,{2,4},
        {3,3},{4,2}
    };
    Solution s;
    s.outerTrees(tree);

}