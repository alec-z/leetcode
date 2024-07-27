#include <string>
#include <iostream>
using namespace std;


class Solution {
    unsigned long long l;
    unsigned long long r;
    unsigned long long ls;
    unsigned long long rs;
    bool isPal(string str) {
        for (int i = 0, j = str.length() - 1; i < j; i++, j--)
            if (str[i] != str[j]) return false;
        return true;
    }
    bool check_palindromes(unsigned long long num) {
        unsigned long long s_num = num * num;
        unsigned long long s_num_tmp = s_num;
        if (num >= ls && num <= rs && s_num >= l && s_num <= r) {
            return isPal(to_string(s_num));
        } else {
            return false;
        }
    }
    int generate_num(unsigned long long num) {
        unsigned long long tmp = num / 10;
        unsigned long long num1 = num;
        unsigned long long num2 = num * 10  + num % 10;
        unsigned long long d;
        int res = 0;
        while (tmp > 0) {
            d = tmp % 10;
            num1 = 10 * num1 + d;
            num2 *= 10 * num2 + d;
            tmp = tmp / 10;
        }
        if (check_palindromes(num1)) res++;
        if (check_palindromes(num2)) res++;
        return res;
    }
public:
    int superpalindromesInRange(string left, string right) {
        l = stoull(left);
        r = stoull(right);
    
        ls = floor(sqrt(l));
        rs = ceil(sqrt(r));
        int rs_h_len = (to_string(rs).size() + 1) / 2;
        int ls_h_len = (to_string(ls).size() + 1) / 2;
        unsigned long long ls_h_s = pow(10, ls_h_len - 1);
        unsigned long long rs_h_e = pow(10, rs_h_len);
        unsigned long long res = 0;
        for (unsigned long long i = 1; i <= 134790409; i++) {
            res += generate_num(i);
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.superpalindromesInRange("398904669", "13479046850");
}