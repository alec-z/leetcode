#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct CTreeNode {
  CTreeNode * parent;
  vector<CTreeNode *> children;
  int nums;
  int children_len;
  int all_len;
  int v;
  public:
  CTreeNode(CTreeNode * parent, int v):parent(parent), v(v), nums(1), children_len(0), all_len(0), children(0) {
  }  
};
class Graph {
    int size_;
    vector<set<int>> adj_;
    CTreeNode * root;
    vector<int> res;
    CTreeNode* get_tree(CTreeNode * parent, int root) {
        CTreeNode * cur = new CTreeNode(parent, root);
        for (int next: adj_[root]) {
            if (parent == nullptr || parent ->v != next) {
                cur->children.push_back(get_tree(cur, next));
            }
        }
        return cur;
    }
    void fill_children_info(CTreeNode * root) {
        int children_len = 0;
        int nums = 1;
        for (auto * c: root->children) {
            fill_children_info(c);
            children_len += c->children_len + c->nums;
            nums += c->nums;
        }
        root->children_len = children_len;
        root->nums = nums;
    }
    void fill_all_info(CTreeNode * root) {
        if (root->parent == nullptr) {
            root->all_len = root->children_len;
        } else {
            int p_direction = root->parent->all_len - (root->children_len + root->nums);
            root->all_len = p_direction + (size_ - root->nums) + root->children_len;
        }
        res[root->v] = root->all_len;
        for (auto* c: root->children)
            fill_all_info(c);
    }
    public:
    Graph(int size, vector<vector<int>>& edges): size_(size), adj_(size), res(size, 0) {
        for (const auto& e: edges) {
            insertEdge(e[0], e[1]);
        }
        root = get_tree(nullptr, 0);
    }
    void insertEdge(int s, int t) {
        adj_[s].insert(t);
        adj_[t].insert(s);
    }
    const set<int> & get_adj(int s) {
        return adj_[s];
    }
    const vector<int> & fill_info() {
        fill_children_info(root);
        fill_all_info(root);
        return this->res;
    }
};

class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        Graph g(n, edges);
        return g.fill_info();
    }
};

int main() {
    int n = 4;
    Solution s;
    vector<vector<int>> edges {
        {2,0},
        {3,1},
        {2,1}
    };
    s.sumOfDistancesInTree(n, edges);
}