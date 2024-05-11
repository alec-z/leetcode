#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
    unordered_map<string, int> words_number;
public:
    int numberForWord(const string & word) {
        auto p = words_number.find(word);
        if (p != words_number.end() && p->second != 1) {
            return p->second;
        }
        if (word.size() == 1) {
            if (p != words_number.end())
                return words_number[word];
            else {
                words_number[word] = 0;
                return 0;
            }
        }
        for (int i = 1; i <= word.size() - 1; i++) {
            auto p = words_number.find(word.substr(0, i));
            if (p != words_number.end() && p->second > 0) {
                int first_part = p->second;
                int second_part = numberForWord(word.substr(i, word.size() - i));
                if (second_part > 0) {
                    words_number[word] = first_part + second_part;
                    return first_part + second_part;
                }
            }
        }
        if (p == words_number.end()) {
            words_number[word] = 0;
        }
        return words_number[word];
    }
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for (string & w: words) {
            words_number[w] = 1;
        }
        vector<string> res;
        for (string & w: words) {
            if (numberForWord(w) >= 2) {
                res.push_back(w);
            }
        }
        return res;
    }
};

int main() {
    vector<string> words {"a","b","ab","abc"};
    Solution s;
    s.findAllConcatenatedWordsInADict(words);
}