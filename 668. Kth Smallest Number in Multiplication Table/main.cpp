#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
    int m;
    int n;

    int le_than(int be, int en, int num) {
        int total = 0;
        for (int i = 1; i <= m; i++) {
            int fl = floor(double(num) / i);
            int bo = ceil(double(be) / i);
            if (fl == 0) break;
            int tmp = min(n, fl) - bo + 1;
            if (tmp > 0)
                total += tmp;
        }
        return total;
    }

    int try_f(int be, int en, int k) {
        int mid = (be + en) / 2;
        if (be == en) {
            return be;
        }
        int le_than_number = le_than(be, en, mid);
        if (le_than_number >= k) {
            return try_f(be, mid, k);
        } else {
            return try_f(mid + 1, en, k - le_than_number);
        }
    }
public:
    int findKthNumber(int m, int n, int k) {
        if (m > n) swap(m, n);
        this->m = m;
        this->n = n;
        return try_f(1, m * n, k);
    }
};

int main() {
    Solution s;
    cout <<s.findKthNumber(9, 9, 81) << endl;
}