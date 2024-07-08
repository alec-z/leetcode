#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    string orderlyQueue(string s, int k) {
        int n = s.size();
        string res;
        if (k == 1) {
            vector<int> cur;
            vector<int> next;
            for (int i = 0; i < n; i++) cur.push_back(i);
            for (int i = 0; i < n; i++) {
                char min_char = 'z' + 1;
                for (int j = 0; j < cur.size(); j++) {
                    if (s[cur[j]] < min_char) {
                        min_char = s[cur[j]];
                    }
                }
                res += min_char;
                next.clear();
                for (auto p: cur) {
                    if (s[p] == min_char) {
                        next.push_back((p + 1) % n);
                    }
                }
                cur = move(next);
            }
            return res;
        } else {
            char* char_array = new char[n + 1];
            strcpy(char_array, s.c_str()); 
            sort(char_array, char_array + (n));
            return string(char_array);
        }
    }
};