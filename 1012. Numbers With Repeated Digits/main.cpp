#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
    int all_different(const string & num, int pos) {
        if (pos > num.size() - 1) return 1;
        int options = 0;
        int cur_d = num[pos] - '0';
        int res = 0;
        for (int d = pos > 0 ? 0 : 1; d < cur_d; d++) {
            bool found = false;
            for (int i = 0; i < pos; i++) {
                if (d == num[i] - '0') {
                    found = true;
                    break;
                }
            }
            if (!found) {
                options++;
            }
        }
        res = options;
        if (options >0) {
            for (int i = pos + 1; i < num.size(); i++) {
                int offset = i - pos;
                if (10 - pos - offset > 0) {
                    res *= (10 - pos - offset);
                } else {
                    res = 0;
                }
            }
        }
        bool found = false;
        for (int i = 0; i < pos; i++) {
            if (cur_d == num[i] - '0') {
                found = true;
                break;
            }
        }
        if (!found) {
            res += all_different(num, pos + 1);
        }
        return res;
    }
    
public:
    int numDupDigitsAtMostN(int n) {
        string n_str = to_string(n);
        int res = 0;
        int all_dif = 0;
        vector<long> size_n = {0, 9, 9*9, 9*9*8, 9*9*8*7, 9*9*8*7*6, 9*9*8*7*6*5,  9*9*8*7*6*5*4,  9*9*8*7*6*5*4*3,  9*9*8*7*6*5*4*3*2,  9*9*8*7*6*5*4*3*2*1};

        for (int i = 1; i <= 10 && i<=n_str.size() - 1; i++) {
            all_dif += size_n[i];
        };
        all_dif += all_different(n_str, 0);
        return n - all_dif;
    }
};

int main() {
    Solution s;
    cout << s.numDupDigitsAtMostN(100);
}