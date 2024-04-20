
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    string numberToWords(int num) {
        vector<string> less_than_20 {
            "Zero", 
            "One",
            "Two",
            "Three",
            "Four",
            "Five",
            "Six",
            "Seven",
            "Eight",
            "Nine",
            "Ten",
            "Eleven",
            "Twelve",
            "Thirteen",
            "Fourteen",
            "Fifteen",
            "Sixteen",
            "Seventeen",
            "Eighteen",
            "Nineteen"
        };
        vector<string> tens {
            "wrongly0",
            "wrongly1",
            "Twenty",
            "Thirty",
            "Forty",
            "Fifty",
            "Sixty",
            "Seventy",
            "Eighty",
            "Ninety"
        };
        auto get_less_than_10 = [&](int a) -> string{
            return less_than_20[a];
        };
        auto get_less_than_100 = [&](int a) -> string{
            if (a < 10) {
                return get_less_than_10(a);
            } else if (a < 20) {
                return less_than_20[a];
            } else {
                string res = tens[a / 10];
                if (a % 10 != 0)
                    res = res + " " +get_less_than_10(a % 10);
                return res;
            }
            return "";
        };

        auto get_less_than_1000 = [&](int a) -> string {
            if (a < 100) {
                return get_less_than_100(a % 100);
            } else if (a < 1000) {
                string res = get_less_than_10(a / 100) + " Hundred";
                if (a % 100 != 0)
                    res = res + " " + get_less_than_100(a % 100);
                return res;
            }
            return "";
        };

        auto get_less_than_1000_000 = [&](int a) -> string {
            if (a < 1000) {
               return get_less_than_1000(a);
            } else if (a < 1000000) {
                string res = get_less_than_1000(a / 1000) + " Thousand";
                if (a % 1000 != 0)
                    res = res + " " + get_less_than_1000(a % 1000);
                return res;
            }
            return "";
        };

        auto get_less_than_1000_000_000 = [&](int a) -> string {
            if (a < 1000000) {
               return get_less_than_1000_000(a);
            } else if (a < 1000000000) {
                string res = get_less_than_1000(a / 1000000) + " Million";
                if (a % 1000000 != 0)
                    res = res + " " + get_less_than_1000_000(a % 1000000);
                return res;
            }
            return "";
        };

        auto get_less_than_1000_000_000_000 = [&](int a) -> string {
            if (a < 1000000000) {
               return get_less_than_1000_000_000(a);
            } else {
                string res = get_less_than_1000(a / 1000000000) + " Billion";
                if (a % 1000000000 != 0)
                    res = res + " " + get_less_than_1000_000_000(a % 1000000000);
                return res;
            }
            return "";
        };

        return get_less_than_1000_000_000_000(num);

    }
};

int main() {
    Solution s;
    cout << s.numberToWords(12345) << endl;
}