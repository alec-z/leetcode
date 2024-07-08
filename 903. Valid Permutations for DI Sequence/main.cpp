#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
const long long mod_p = 10e9 + 7;
class Solution {
public:
    int numPermsDISequence(string s) {
        int n = s.size();
        vector<long long> cur(n + 1, 0);
        vector<long long> next(n + 1, 0);
        vector<long long> tmp;
        if (s[0] == 'I')
            cur[1] = 1;
        else {
            cur[0] = 1;
        }
        for (int i = 1; i < n; i++) {
            char c = s[i];
            int len = i + 1;
            if (c == 'I') {
                next[0] = 0;
                for (int j = 1; j <= len; j++) {
                     next[j] = (next[j - 1] + cur[j - 1]) % mod_p;
                }
            } else {
                next[len] = 0;
                for (int j = len - 1; j >= 0; j--) {
                     next[j] = (next[j + 1] + cur[j]) % mod_p;
                }
            }
            tmp = move(cur);
            cur = move(next);
            next = move(tmp);
        }
        long long  all = 0;
        for (int i = 0; i < n + 1; i++) {
            all+= cur[i];
            all = all % mod_p;
        }
        return all;

    }
};