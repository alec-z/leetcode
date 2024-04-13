#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  class Resolution {
    public:
    const int HASH_SIZE = 5000;
    Resolution(const string &str, const vector<string> &wordDict)
        : input_str(str),
          search_res(HASH_SIZE),
          top(-1),
          wordDict(wordDict),
          hash_map(HASH_SIZE) {
      for (int i = 0; i < wordDict.size(); i++) {
        size_t hash_code_n =
            hash_code(wordDict[i], 0, wordDict[i].size()) % HASH_SIZE;
        hash_map[hash_code_n].push_back(i);
      }
    }
    const string &input_str;
    vector<int> search_res;
    int top = -1;
    const vector<string> &wordDict;
    vector<vector<int>> hash_map;
    vector<string> res;

    size_t hash_code(const string &s, int start, int end) {
      size_t res = 31;
      for (int i = start; i < end; i++) {
        res = (res * 31) + s[i];
      }
      return res;
    }

    bool check_exist(int start, int end) {
      size_t h = hash_code(input_str, start, end) % HASH_SIZE;
      for (auto p : hash_map[h]) {
        int i = start;
        for (; i < end; i++) {
            if (input_str[i] != wordDict[p][i - start]) {
                break;
            }
        }
        if (i == end && wordDict[p].size() == end - start) {
            return true;
        }
      }
      return false;
    }

    void push_res() {
      int be = 0;
      string tmp = "";
      for (int i = 0; i <= top; i++) {
        if (i > 0) tmp += " ";
        int l = search_res[i] - be;
        tmp += input_str.substr(be, l);
        be += l;
      }
      res.push_back(tmp);
    }

    void tryWordBreak(int start) {
      if (start == input_str.size()) {
        push_res();
      };
      for (int i = start; i < input_str.size(); i++) {
        if (check_exist(start, i + 1)) {
          search_res[++top] = (i + 1);
          tryWordBreak(i + 1);
          top--;
        }
      }
    }
  };
  vector<string> wordBreak(string s, vector<string> &wordDict) {
    Resolution re_sol(s, wordDict);
    re_sol.tryWordBreak(0);
    return re_sol.res;
  }
};

int main() {
    Solution s;
    vector<string> wordDict  {"cat","cats","and","sand","dog"};
    auto p = s.wordBreak("catsanddog",wordDict);
    int c = 1;
}