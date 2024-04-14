#include <string>
#include <vector>
#include <map>
#include <limits>
#include <iostream>
using namespace std;

class Solution {
private:
    map<tuple<int, int, int>, int> func;
    string str;
    int try_f(int left, int i, int j) {
        if (i > j) return 0;
        tuple<int, int, int> tuple = make_tuple(left, i, j);
        if (func.find(tuple) != func.end()) {
            return func[tuple];
        }
        bool all_left = true;
        for (int k = i; k <= j; k++) {
            if (str[k] != 'a' + left) {
                all_left = false;
                break;
            }   
        }
        if (all_left) {
            func[tuple] = 0;
            return 0;
        }
        if (i == j) {
            func[tuple] = 1;
            return 1;
        }
        char cur_char = str[j];
        int min_step;
        int tmp = 0;
        if ('a' + left == cur_char) {
            min_step = try_f(left, i, j - 1);
        } else {
            min_step = try_f(left, i, j - 1) + 1;
        }
        
        for (int k = j - 1; k >= i; k--) {
            if (str[k] == cur_char) {
                tmp = try_f(left, i, k - 1);
                tmp += 1;
                tmp += try_f(str[k] - 'a', k + 1, j - 1);
                if (tmp < min_step) {
                    min_step = tmp;
                }
            }
        }
        func[tuple] = min_step;
        return min_step;
    }
public:
    int strangePrinter(string s) {
        str = "";
        str += s[0];
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != str[str.size() - 1]) {
                str += s[i];
            }
        }
        return try_f(26, 0, str.size() - 1);
    }
};

int main() {
    Solution s;
    cout <<s.strangePrinter("aabbb") <<endl;
}