#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <iostream>

using namespace std;



class Solution {
private:
    bool check_palindrome_head(const string& str, int len) {
        if (len == 0 || len == 1) return true;
        for (int j = 0; j < len / 2; j++) {
            if (str[j] != str[len - 1 - j]) {
                return false;
            }
        }
        return true;
    }
    bool check_palindrome_tail(const string& str, int len) {
        if (len == 0 || len == 1) return true;
        int start = str.size() - len;
        for (int j = 0 ; j < len / 2; j++) {
            if (str[start + j] != str[start + len - 1 - j]) {
                return false;
            }
        }
        return true;
    }
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> words_set, reverse_words_set;

        auto hash_f = [](const pair<int,int> &x) -> size_t
        { 
            return x.first ^ x.second; 
        };
        unordered_set<pair<int,int>, decltype(hash_f)> res(0, hash_f);
        vector<vector<int>> res_v;
        for (int i = 0; i < words.size(); i++) {
            words_set[words[i]] = i;
        }      
        for (int i = 0; i < words.size(); i++) {
            string word = words[i];
            for (int len = 0; len <= word.size(); len++) {
                if (check_palindrome_head(word, len)) {
                    string remain = word.substr(len, word.size() - len);
                    reverse(remain.begin(), remain.end());
                    if (words_set.find(remain) != words_set.end()) {
                        int j = words_set[remain];
                        if (i != j)
                            res.insert(make_pair(j, i));
                    }                  
                }
                if (check_palindrome_tail(word, len)) {
                    string remain = word.substr(0, word.size() - len);
                    reverse(remain.begin(), remain.end());
                    if (words_set.find(remain) != words_set.end()) {
                        int j = words_set[remain];
                        if (i != j)
                            res.insert(make_pair(i,j));
                    }       
                }
            }
        }
        for (auto p : res) {
            res_v.push_back({p.first, p.second});
        }
        return res_v;
    }
};

int main() {
    Solution s;
    vector<string> words {"abcd","dcba","lls","s","sssll"};
    vector<vector<int>> res = s.palindromePairs(words);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i][0] << " " << res[i][1] << endl;
    }

}