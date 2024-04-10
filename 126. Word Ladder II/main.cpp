#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
    vector<vector<string>> get_result(vector<string>& wordList, vector<vector<int>> & v_to, int tail) {
        vector<vector<string>> res;
        if (tail == wordList.size() - 1) {
            res.push_back({wordList[wordList.size() - 1]});
            return res;
        }
        for (int pre: v_to[tail]) {
            for (vector<string> & pre_v_s : get_result(wordList, v_to, pre)) {
                pre_v_s.push_back(wordList[tail]);
                res.push_back(pre_v_s);
            }
        }
        return res;
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int MAX_INT = numeric_limits<int>::max();

        wordList.push_back(beginWord);
        int len = wordList.size();
        vector<vector<string>> res;
        queue<int> q;
        vector<vector<int>> v_to(len);
        vector<int> step_to(len, MAX_INT);


        q.push(wordList.size() - 1);
        step_to[len - 1] = 0;

        int target = -1;
        for (int i = 0; i < len - 1; i++) {
            if (wordList[i] == endWord) {
                target = i;
                break;
            }
        }

        if (target == -1) {
            return res;
        }

        auto adj = [&wordList](int v, int i) -> bool {
            string & word_v = wordList[v];
            string & word_i = wordList[i];
            if (word_v.size() != word_i.size()) {
                return false;
            }
            int different = 0;
            for (int i = 0; i < word_v.size(); i++) {
                if (word_v[i] != word_i[i]) {
                    different++;
                }
            }
            return (different == 1);
        };

        int shortest = MAX_INT;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            int step_v = step_to[v];
            if (step_v == shortest) break;
            for (int i = 0; i < len - 1; i++) {
                if ((step_to[i] == MAX_INT || step_to[i] == step_v + 1) && adj(v, i)) {
                    if (step_to[i] == MAX_INT)  q.push(i);
                    v_to[i].push_back(v);
                    step_to[i] = step_v + 1;
                    if (i == target ) {
                        shortest = step_to[target];
                    }
                }
            }
        }
        if (!v_to[target].empty()) {
            res = get_result(wordList, v_to, target);
        }
        return res;
    }
};

int main() {
    vector<string> words {"hot","dot","dog","lot","log","cog"};
    Solution s;
    auto res = s.findLadders("hit", "cog", words);
    int c = 1;
    
}