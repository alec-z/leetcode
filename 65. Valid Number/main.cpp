#include <string>
#include <regex>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        const string integer_str = R"(((\+|-)?(\d+)))";
        const string decimal_str = R"(((\+|-)?(\d+\.|\d+\.\d+|\.(\d)+)))";
        const string e_part_str = "((e|E)" + integer_str + ")?";
        const string number_str = "^(" + integer_str + "|"  + decimal_str + ")"  + e_part_str + "$";
        const regex number(number_str);
        return regex_match(s, number);
    }
};

int main() {
    Solution s;
    cout <<s.isNumber("+.8") << endl;
}