#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    int palindromePartition(string s, int k) {
        int n = s.size();
        int work[100][100] = {0};
        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < n + 1 - l; i++) {
                work[i][i + l -1] = work[i+1][i + l - 2] + (s[i] != s[i + l - 1]);
            }
        }
        int f[2][100] = {0};
        for (int i = 0; i < n; i++) f[1][i] = work[0][i];
        for (int ik = 2; ik <= k; ik++) {
            for (int p = ik - 1; p < n; p++) {
                f[ik & 1][p] = f[(ik-1) & 1][p - 1];
                for (int l = 2; p - l + 1  >= ik - 1; l++)
                    f[ik & 1][p] = min(f[ik & 1][p], f[(ik - 1) & 1][p - l] + work[p - l + 1][p]);
                
            }
        }
        return f[k & 1][n - 1];
    }
};

int main() {
    Solution s;
    cout << s.palindromePartition(string("ihhyviwv"), 7);
}