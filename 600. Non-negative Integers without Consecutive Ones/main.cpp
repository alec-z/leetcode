#include <cmath>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Solution {
    vector<int> f_bits;
    map<int, int> func;
    int try_f(int n) {
        if (func.find(n) != func.end()) {
            return func[n];
        }
        int bits = ceil(log2(n + 1));
        int first_1 = pow(2, bits - 1);
        int first_2_1 = first_1 + pow(2, bits - 2);
        if (n >= first_2_1) {
            func[n] = f_bits[bits - 1] + try_f(pow(2, bits- 2) - 1);
            return func[n];
        }
        else {
            func[n] = f_bits[bits - 1] + try_f(n - first_1);
            return func[n];
        }
    }
public:
    int findIntegers(int n) {
        int bits = ceil(log2(n + 1));
        f_bits.resize(bits + 1, 0);
        f_bits[0] = 1;
        f_bits[1] = 2;
        for (int i = 2; i <= bits; i++) {
            f_bits[i] = f_bits[i - 2] + f_bits[i - 1];
        }
        func[0] = 1;
        func[1] = 2;
        func[2] = 3;
        func[3] = 3;
        func[4] = 4;
        func[5] = 5;
        func[6] = 5;
        func[7] = 5;
        return try_f(n);
    }
};

int main() {
    Solution s;
    cout << s.findIntegers(12) << endl;;
}