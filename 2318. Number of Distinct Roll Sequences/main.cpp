#include <vector>
using namespace std;
unsigned int mod_p = 1e9 + 7;
class Solution {
    private: 
    int gcd(int a, int b) {
        if (a < b) swap(a, b);
        if (b == 0) return a;
        return gcd(b, a % b);
    }
    void zeros(vector<vector<unsigned>> & arr) {
        for (int i = 0; i <= 6; i++) {
            for (int j = 0; j <=6; j++) {
                arr[i][j] = 0;
            }
        }
    }


public:
    int distinctSequences(int n) {
        vector<vector<unsigned>> pre(7, vector<unsigned>(7, 0)), next(7, vector<unsigned>(7, 0)), tmp(7, vector<unsigned>(7, 0));
        pre[1][2] = 1;
        pre[1][3] = 1;
        pre[1][4] = 1;
        pre[1][5] = 1;
        pre[1][6] = 1; // 5

        pre[2][1] = 1;
        pre[2][3] = 1;
        pre[2][5] = 1; // 3


        pre[3][1] = 1;
        pre[3][2] = 1;
        pre[3][4] = 1;
        pre[3][5] = 1; // 4

        pre[4][1] = 1;
        pre[4][3] = 1;
        pre[4][5] = 1; // 3

        pre[5][1] = 1;
        pre[5][2] = 1;
        pre[5][3] = 1;
        pre[5][4] = 1;
        pre[5][6] = 1; // 5

        pre[6][1] = 1;
        pre[6][5] = 1; // 2

        if (n == 1) {
            return 6;
        } else if (n == 2) {
            return 22;
        }

        for (int i = 3; i <= n; i++) {
            zeros(next);
            for (int c = 1; c <= 6; c++) {
                for (int c1 = 1; c1 <= 6; c1++) {
                    for (int c2 = 1; c2 <= 6; c2++) {
                        if (c==c2) {
                            continue;
                        }
                        if (gcd(c, c1) > 1) {
                            continue;
                        }
                        if (c == c1) {
                            continue;
                        }
                        next[c][c1] += pre[c1][c2];
                        next[c][c1] %= mod_p;
                        
                    }
                }
            }
            tmp = std::move(pre);
            pre = std::move(next);
            next = std::move(tmp);
        }
        int sum = 0;
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <=6; j++) {
                sum += pre[i][j];
                sum %= mod_p;
            }
        }
        return sum;

    }
};