#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;


class Solution {
    set<tuple<char, char, char>> board_set;
    vector<vector<bool>> mark;
public:
    bool dfs(int index, string & word, int pos, char r, char l) {
        if (pos == word.size() - 1) {
            return true;
        }
        mark[r][l] = true;
        char next_c = word[pos + 1];
        auto p_top = board_set.find(make_tuple(next_c, r - 1, l));
        if (p_top != board_set.end()) {
            if (!mark[r - 1][l] && dfs(index, word, pos + 1, r - 1, l)) {
                mark[r][l] = false;
                return true;
            }
        }

        auto p_right = board_set.find(make_tuple(next_c, r , l + 1));
        if (p_right != board_set.end()) {
            if (!mark[r][l+1] && dfs(index, word, pos + 1, r , l + 1)) {
                mark[r][l] = false;
                return true;
            }
        }

        auto p_bottom = board_set.find(make_tuple(next_c, r + 1, l));
        if (p_bottom != board_set.end()) {
            if (!mark[r+1][l] && dfs(index, word, pos + 1, r + 1, l)) { 
                mark[r][l] = false;
                return true;
            }
        }

        auto p_left = board_set.find(make_tuple(next_c, r, l - 1));
        if (p_left != board_set.end()) {
            if (!mark[r][l-1] && dfs(index, word, pos + 1, r , l - 1)) {
                mark[r][l] = false;
                return true;
            }
        }
        mark[r][l] = false;
        return false;
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        mark.resize(board.size());
        for (char i = 0; i < board.size(); i++) {
            mark[i].resize(board[i].size(), false);
            for (char j = 0; j < board[i].size(); j++) {
                board_set.insert(make_tuple(board[i][j], i, j));
            }
        }
        vector<string> res;
        for (int i = 0; i < words.size(); i++) {
            string & word = words[i];
            auto p_char = board_set.lower_bound(make_tuple(word[0], (char)0, (char)0));
            while (p_char!= board_set.end() && get<0>(*p_char) == word[0]) {
                if (dfs(i, word, 0, get<1>(*p_char), get<2>(*p_char))) {
                    res.push_back(word);
                    break;
                }
                p_char++;
            }
        }
        return res;
    }
};