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

#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
    TreeNode* tryRecover(string traversal) {
        if (traversal == "") return nullptr;
        int p = 0;
        int len = traversal.size();
        stringstream root_num_ss;
        int root_num;
        while (p < len && traversal[p] != '-') {
            root_num_ss <<  traversal[p];
            p++;
        }
        root_num_ss >> root_num;
        stringstream left_ss;
        int current_token_dash_num = 0;
        p++;
        while (p < len) {
            if (traversal[p] == '-') {
                if (traversal[p - 1] != '-') {
                    current_token_dash_num = 1;
                } else {
                    current_token_dash_num++;
                }
                if (current_token_dash_num > 1) {
                    left_ss << traversal[p];
                }
            } else {
                if (current_token_dash_num == 1) {
                    break;
                } else {
                    left_ss << traversal[p];
                }
            }
            p++;
        }
        TreeNode * left_tree = tryRecover(left_ss.str());
        stringstream right_ss;
        current_token_dash_num = 0;
        while (p < len) {
            if (traversal[p] == '-') {
                if (traversal[p - 1] != '-') {
                    current_token_dash_num = 1;
                } else {
                    current_token_dash_num++;
                }
                if (current_token_dash_num > 1) {
                    right_ss << traversal[p];
                }
            } else {
                if (current_token_dash_num == 1) {
                    break;
                } else {
                    right_ss << traversal[p];
                }
            }
            p++;
        }

        TreeNode * right_tree = tryRecover(right_ss.str());
        return new TreeNode(root_num, left_tree, right_tree);
    }
public:
    TreeNode* recoverFromPreorder(string traversal) {
        return tryRecover(traversal);
    }
};
