#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


class Solution {
int res = 0;
vector<int> power, power_acc;
void tryKthNumber(int level, int n, int k) {
    int total = 0;
    if (level == 1 && n <= 9) {
        res = k + 1;
        return;
    } 
    if (level ==0) total = 1;
    if (level == 0 && k == 0) return;

    for (int i = level; i <= 9; i++) {
        int all_number = allNumber(res, i, n);
        if (total + all_number > k) {
            res *= 10;
            res += i;
            tryKthNumber(0, n, k - total);
            break;
        } else {
            total+= all_number;
        }
    }
}

int allNumber(int res, int first_d, int n) {
    res *= 10;
    res += first_d;
    int res_len = to_string(res).size();
    string n_str = to_string(n);
    int n_len = to_string(n).size();
    int header = n / power[n_len - res_len];
    if (res < header) {
        return power_acc[n_len - res_len];
    } else if (res > header) {
        if (n_len - res_len - 1 >=0) {
            return power_acc[n_len - res_len - 1];
        } else {
            return 0;
        }
    } else {
        int total = 1;
        if (res_len < n_len) {
            for (int i = 0; i<=9; i++)
                total += allNumber(res, i, n);
        }
        return total;
    }
}
public:
    int findKthNumber(int n, int k) {
        power.resize(20, 0);
        power_acc.resize(20,0);
        power[0] = 1;
        power_acc[0] = 1;
        for (int i = 1; i < 10; i++) {
            power[i] = power[i - 1] * 10;
            power_acc[i] = power_acc[i - 1] + power[i];
        }
        res = 0;
        tryKthNumber(1, n, k - 1);
        return res;
    }
};

int main() {
    Solution s;
    cout << s.findKthNumber(10000, 1) << endl;
}