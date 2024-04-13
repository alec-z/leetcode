#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;
class Solution {
    long long get_p_val(const string & half, bool odd) {

        string first = half;
        string second = half;
        reverse(second.begin(), second.end());
        long long res;
        if (odd) {
            stringstream res_stream(first + second.substr(1, second.size() - 1));
            res_stream >> res;
        } else {
            stringstream res_stream(first + second);
            res_stream >> res;
        }
        return res;
    }
public:
    string nearestPalindromic(string n) {
        long long n_val;
        long long res = -1;;
        stringstream n_stream(n);
        n_stream >> n_val;
        int n_len = n.size();
        string half_n = n.substr(0, (n_len + 1) / 2); 
        long long p_val =  get_p_val(half_n, n_len % 2 == 1);
        long long min_diff = numeric_limits<long long>::max();
        if (abs(p_val - n_val) > 0) {
            min_diff = abs(p_val - n_val);
            res = p_val;
        }
        long long half_n_val;

        stringstream(half_n) >> half_n_val;
        half_n_val--;
        if (to_string(half_n_val).size() == half_n.size()) {
            p_val = get_p_val(to_string(half_n_val), n_len % 2 == 1);
            if (abs(p_val - n_val) < min_diff || (abs(p_val - n_val) == min_diff && p_val < res)) {
                min_diff = abs(p_val - n_val);
                res = p_val;
            }
        }

        stringstream(half_n) >> half_n_val;
        half_n_val++;
        if (to_string(half_n_val).size() == half_n.size()) {
            p_val = get_p_val(to_string(half_n_val), n_len % 2 == 1);
            if (abs(p_val - n_val) < min_diff || (abs(p_val - n_val) == min_diff && p_val < res) ) {
                min_diff = abs(p_val - n_val);
                res = p_val;
            }
        }

        p_val = pow(10, n_len - 1) - 1;
        if (abs(p_val - n_val) < min_diff || (abs(p_val - n_val) == min_diff && p_val < res) ) {
            min_diff = abs(p_val - n_val);
            res = p_val;
        }

        p_val = pow(10, n_len) + 1;
        if (abs(p_val - n_val) < min_diff || (abs(p_val - n_val) == min_diff && p_val < res) ) {
            min_diff = abs(p_val - n_val);
            res = p_val;
        }
        return to_string(res);        
    }
};
