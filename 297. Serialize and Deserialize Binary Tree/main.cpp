#include <string>
#include <vector>
#include <limits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

const short MIN_SHORT = numeric_limits<short>::min();

class Codec {
    vector<short> shorts;
    int p;
    void try_serialize(TreeNode* root) {
        if (root == NULL) return;
        shorts.push_back(root->val);
        shorts.push_back(0);
        int p_left_number = shorts.size() - 1;
        try_serialize(root->left);
        shorts[p_left_number] = shorts.size() - (p_left_number + 1);
        try_serialize(root->right);
    }

    TreeNode* try_deserialize(int end) {
        if (p == end) return NULL;
        TreeNode * node = new TreeNode(shorts[p]);
        p++;
        int left_len = shorts[p];
        p++;
        node->left = try_deserialize(p + left_len);
        node->right = try_deserialize(end);
        return node;
    }
    

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        shorts.resize(0);
        try_serialize(root);
        vector<unsigned char> res;
        for (int i = 0; i < shorts.size(); i++) {
            res.push_back((unsigned char) ((shorts[i] & 0xFF00) >> 8 & 0x00FF));
            res.push_back((unsigned char) (shorts[i] & 0x00FF));
        }
        return string(res.begin(), res.end());
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        p = 0;
        vector<unsigned char> tmp(data.begin(), data.end());
        shorts.resize(tmp.size() / 2);
        for (int i = 0; i < shorts.size(); i ++) {
            shorts[i] = (tmp[2*i] << 8) | (unsigned short)tmp[2*i + 1];
        }
        TreeNode *node = try_deserialize(shorts.size());
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main() {
    unsigned short c = 10000;
    c = c & 0xFF00;

    TreeNode *node1 = new TreeNode(1);
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node3 = new TreeNode(3);
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node5 = new TreeNode(5);

    node1->left = node2;
    node1->right = node3;
    
    node3->left = node4;
    node3->right = node5;

    Codec coder;
    auto str = coder.serialize(node1);
    TreeNode * res = coder.deserialize(str);
    int p = 1;
}