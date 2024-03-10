#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


class Solution {
vector<int> power, power_acc;
int len;
public:
    int findKthNumber(int n, int k) {
        k--;
        power.resize(9, 0);
        power_acc.resize(9,0);
        power[0] = 1;
        power_acc[0] = 1;
        for (int i = 1; i < 10; i++) {
            power[i] = power[i - 1] * 10;
            power_acc[i] = power_acc[i - 1] + power[i];
        }
        len = to_string(n).size();
        int i = len - 1;

        if (i == 0) {
            return k + 1;
        }


        int res = 0;
      
        int first_d = (k / power_acc[i]) + 1;
        k = k % power_acc[i];
        
        
        res = first_d;
        while (i >= 0) {
            i--;
            if (k == 0) {
                return res;
            } else {
                k--;
                int first_d = (k / power_acc[i]);
                k = k % power_acc[i];
                res = res * 10 + first_d;
            }
        }
        
        return res;
    }
};

int main() {
    Solution s;
    cout << s.findKthNumber(33, 20) << endl;
}