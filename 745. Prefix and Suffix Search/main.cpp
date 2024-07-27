#include <string>
#include <map>
#include <iostream>
using namespace std;

class WordFilter {
    map<string, int> s_map;
public:
    WordFilter(vector<string>& words): s_map() {
        for (int k = 0; k < words.size(); k++) {
            string &w = words[k];
            string pre = "";
            for (int i = 0; i < w.size(); i++) {
                pre += w[i];
                string suf = "";
                for (int j = w.size() - 1; j >= 0; j--) {
                    suf = w[j] + suf;
                    string s_k = pre + '|' + suf;
                    s_map[s_k] = k;                    
                }
            }
        }
    }
    
    int f(string pref, string suff) {
        auto p = s_map.find(pref + '|' + suff);
        if (p == s_map.end()) return -1;
        else return p->second;
    }
};

int main() {
    vector<string>words {"abbba", "abba"};
    WordFilter wordFilter(words);
    cout << wordFilter.f("ab", "ba");

}

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(pref,suff);
 */