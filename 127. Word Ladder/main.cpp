#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int MAX_INT = numeric_limits<int>::max();

        wordList.push_back(beginWord);
        int len = wordList.size();
        queue<int> q;
        vector<int> v_to(len, -1);
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
            return 0;
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
            for (int i = 0; i < len - 1; i++) {
                if (step_to[i] == MAX_INT && adj(v, i)) {
                    v_to[i] = v;
                    if (i == target ) {
                        return step_to[v] + 2;
                    } else {
                        step_to[i] = step_to[v] + 1;
                        q.push(i);
                    }
                }
            }
        }
        return 0;
    }
};