#include <vector>
#include <list>
#include <stack>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Solution {
    vector<char>try_operators;
    vector<string> res_str;
    long target;
    string num;
    int op_len;
    vector<long> numbers;
    vector<char> operators;
    vector<long> n_numbers;
    vector<char> n_operators;
    void cal() {
        int top_n = 0;
        int top_op = 0;
        numbers[top_n++] = num[0] - '0';
        for (int i = 0; i < op_len; i++) {
            switch (try_operators[i]) {
                case ' ':
                    if (numbers[top_n - 1] == 0)
                        return;
                    numbers[top_n - 1] = numbers[top_n - 1] * 10 + (num[i + 1] - '0');
                    break;
                case '*':
                case '+':
                case '-':
                    operators[top_op++] = (try_operators[i]);
                    numbers[top_n++] = (num[i + 1] - '0');
                    break;
            }
        }
        int top_n_n = 0;
        int top_n_op = 0;
        n_numbers[top_n_n++] = numbers[0];
        for (int i = 0; i < top_op; i++) {
            if (operators[i] == '*') {
                n_numbers[top_n_n - 1] = n_numbers[top_n_n - 1] * numbers[i + 1];
            } else {
                n_numbers[top_n_n++] = numbers[i+1];
                n_operators[top_n_op++] = operators[i];
            }
        }
        long res = n_numbers[0];
        
        for (int i = 0; i < top_n_op; i++) {
            if (n_operators[i] == '+') {
                res += n_numbers[i + 1];
            } else if (n_operators[i] == '-') {
                res -= n_numbers[i + 1];
            }
        }

        if (res == target) {
             ostringstream oss;
             oss << numbers[0];
             for (int i = 0; i < top_op; i++) {
                oss << operators[i];
                oss << numbers[i + 1];
             }
             res_str.push_back(oss.str());
        }
    }
    void try_op(int pos) {
        if (pos == num.size() - 1) {
            cal();
        } else {
            try_operators[pos] = ' ';
            try_op(pos + 1);
            try_operators[pos] = '+';
            try_op(pos + 1);
            try_operators[pos] = '-';
            try_op(pos + 1);
            try_operators[pos] = '*';
            try_op(pos + 1);
        }
    }
public:
    vector<string> addOperators(string num, int target) {
       this->num = num;
       this->target = target;
       this->op_len = num.size() - 1;
     
       try_operators.resize(op_len + 2);
       numbers.resize(op_len + 2);
       operators.resize(op_len + 2);
       n_numbers.resize(op_len + 2);
       n_operators.resize(op_len + 2);


       try_op(0);
       return res_str;
    }
};

int main() {
    Solution s;
    for (auto & s:s.addOperators("123", 6)) {
        cout << s << endl;
    }
}