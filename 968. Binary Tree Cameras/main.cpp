/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#include <set>
#include <map>
using namespace std;
class Solution {
    map<int, set<TreeNode*>> l_set;
    map<TreeNode*, TreeNode*> p_map;
    void dfs(TreeNode* root,int level, TreeNode *parent) {
        if (root == nullptr) return;
        p_map[root] = parent;
        l_set[level].insert(root);
        dfs(root->left, level+1, root);
        dfs(root->right, level+1, root);
    }
public:
    int minCameraCover(TreeNode* root) {
        int total = 0;
        dfs(root, 0, nullptr);
        while (!l_set.empty()) {
            auto p = l_set.rbegin();
            if (p -> second.empty()) {
                l_set.erase(p->first);
                continue;
            }
            auto cur_node = *(p->second.begin());
            auto cnl = p->first;
            auto c_node = p_map[cur_node];
            if (c_node == nullptr) {
                total++;
                break;
            }
            total++;
            l_set[cnl - 1].erase(c_node);
            if (c_node->left) {
                l_set[cnl].erase(c_node -> left);
            }
            if (c_node->right) {
                l_set[cnl].erase(c_node-> right);
            }
            auto p_c_node = p_map[c_node];
            if (p_c_node != nullptr) {
                l_set[cnl - 2].erase(p_c_node);
            }
        }
            return total;
    }
};