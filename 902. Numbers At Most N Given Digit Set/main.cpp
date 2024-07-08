#include <string>
#include <vector>
using namespace std;
class Solution {
    int most(vector<string>& digits, int n, bool small_len) {
        string n_str = to_string(n);
        int len = n_str.size();
        int d_n = digits.size();
        int first_d = n / (pow(10, len -1));
        int sum = 0;
        if (small_len) {
            for (int i = 1; i < len; i ++) {
                sum += pow(d_n, i);
            }
        }
        for (int i = 0; i < d_n; i++) {
            if (stoi(digits[i]) < first_d) {
                sum += pow(d_n, len - 1);
            } else if (stoi(digits[i]) == first_d) {
                if (len == 1) sum++;
                else {
                    if (n_str[1] !='0') { 
                        sum += most(digits, n % (int)pow(10, len - 1), false);
                    }
                }
                break;
            } else {
                break;
            }
        }
        return sum;

    }
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
       return  most(digits, n, true);
    }
};