#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
struct TrieNode {
    map<char, TrieNode *> children;
    int index;
    TrieNode() {
        this->index = -1;
    }
};

class Solution {
    TrieNode root;
    vector<vector<bool>> mark;
    vector<vector<char>> *board;
    set<int> res;
    int m;
    int n;
public:
    void dfs(TrieNode * node, int r, char l) {
        mark[r][l] = true;

        if (node -> index > -1) {
            res.insert(node->index);
        }

        char next_char;
        if (r - 1 >= 0 && !mark[r - 1][l]) {
            next_char = (*board)[r - 1][l];
            if (node->children[next_char] != nullptr) {
                dfs(node->children[next_char], r - 1, l);
            }
        }

        if (l + 1 < n && !mark[r][l + 1]) {
            next_char = (*board)[r][l + 1];
            if (node->children[next_char] != nullptr) {
                dfs(node->children[next_char], r, l + 1);
            }
        }


        if (r + 1 < m && !mark[r + 1][l]) {
            next_char = (*board)[r + 1][l];
            if (node->children[next_char] != nullptr) {
                dfs(node->children[next_char], r + 1, l);
            }
        }

        if (l - 1 >= 0 && !mark[r][l - 1]) {
            next_char = (*board)[r][l - 1];
            if (node->children[next_char] != nullptr) {
                dfs(node->children[next_char], r, l - 1);
            }
        }

        mark[r][l] = false;
    }
    void put(const string & word, int index, TrieNode &root) {
        TrieNode *p = &root;
        for (char c: word) {
            auto tmp = p->children[c];
            if (tmp != nullptr) {
                p = tmp;
            } else {
                p->children[c] = new TrieNode();
                p = p->children[c];
            }
        }
        p -> index = index;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        this->board = &board;
        this -> m = board.size();
        this -> n = board[0].size();
        mark.resize(m);
        for (int i = 0; i < m; i++) mark[i].resize(n);
        for (int i = 0; i < words.size(); i++) {
            put(words[i], i, root);
        }
        for (int r = 0; r < m; r ++) {
            for (int l = 0; l < n; l ++) {
                if (root.children[board[r][l]] != nullptr) {
                    dfs(root.children[board[r][l]], r, l);
                }
            }
        }
        vector<string> res_str;
        for (auto i : res) {
            res_str.push_back(words[i]);
        }
        return res_str;
    } 
};
int main() {
    return 0;
}