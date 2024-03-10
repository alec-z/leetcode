#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int times = minutesToTest / minutesToDie;
        int top_p = ceil(log2(buckets));
        vector<vector<int>> f;
        f.resize(times + 1);
        for (int i = 0; i <= times; i++) f[i].resize(top_p + 1, 0);
        f[1][0] = 0;
        for (int p = 1; p <= top_p; p++) {
            f[1][p] = pow(2, p); 
            if (1 == times && f[1][p] >= buckets) {
                return p;
            }
        }
        for (int k = 2; k <= times; k++) {
            f[k][0] = 0;
            for (int p = 1; p <= top_p; p++) {
                int sum = 0;
                int die_p_nums = 1;
                for (int die_p = 0; die_p <= p; die_p++) {
                    if (die_p == 0 || die_p == p) {
                        die_p_nums = 1;
                    } else {
                        die_p_nums = die_p_nums * (p - die_p + 1) / die_p;
                    }
                    if (p == die_p) {
                        sum++;
                    } else {
                        sum += die_p_nums * f[k - 1][p - die_p];
                    }
                }
                f[k][p] = sum;
                if (k == times && sum >= buckets ) {
                    return p;
                }
            }
        }   
        return top_p;
    }
};

int main() {
    Solution s;
    cout << s.poorPigs(5, 15, 60) << endl;
}