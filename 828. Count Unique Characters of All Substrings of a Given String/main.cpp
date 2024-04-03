#include <iostream>
#include <string>
using namespace std;


class Solution {
    int a[100001][26];
    int getUnique(int i, int k) {
        int k_pre_location = a[i][k];
        if (k_pre_location == -1) return 0;
        else {
            if (k_pre_location == 0) {
                return k_pre_location + 1;
            } else 
            return k_pre_location - a[k_pre_location - 1][k];
        }
    }
public:
    int uniqueLetterString(string s) {
    
        for (int k = 0; k < 26; k++) {
            a[0][k] = -1;
        }
        a[0][s[0] - 'A'] = 0;

        for (int i = 1; i < s.size(); i++) {
            for (int k = 0; k < 26; k++) {
                a[i][k] = a[i - 1][k];
            }
            a[i][s[i] - 'A'] = i;
        }

        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            for (int k = 0; k < 26; k++) {
                res += getUnique(i, k);
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    string str =  "ABA";
    cout << s.uniqueLetterString(str) << endl;
}