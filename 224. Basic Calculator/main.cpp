#include <string>
#include <stack>
#include <iostream>
using namespace std;

struct Token {
    int t_type; // 0 for number, 1 for other token, -1 for end;
    int number;
    char token;
};

class Solution {
    Token getNextToken(string& s, int & i) {
        while (i < s.size() && s[i] == ' ') {
            i++;
        }
        if (i == s.size()) return {-1};
        Token res;
        char first_char = s[i];
        if (first_char >= '0' && first_char <= '9') {
            res.t_type = 0;
            res.number = 0;
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                res.number = res.number * 10 + (s[i] - '0');
                i++;
            }
        } else {
            res.t_type = 1;
            res.token = s[i];
            i++;
        }
        return res;
    }
    void insertNumber(stack<Token> &stacks, Token num) {
        if (stacks.empty()) stacks.push(num);
        // should only be type 1;
        switch (stacks.top().token)
        {
        case '+':
            stacks.pop();
            if (stacks.top().t_type == 0)
                stacks.top().number += num.number;
            else {
                stacks.push(num);
            }
                
            
            break;
        case '-':
            stacks.pop();
            if (stacks.top().t_type == 0)
                stacks.top().number -= num.number;
            else {
                num.number = - num.number;
                stacks.push(num);
            }
            break;
        case '(':
            stacks.push(num);
            break;
        default:
            break;
        }
    }
    void insertToken(stack<Token> &stacks, Token token) {
        if (stacks.empty()) stacks.push(token);
        // should only be type 1;
        if (token.token == ')') {
            auto num = stacks.top();
            stacks.pop();
            stacks.pop();
            insertNumber(stacks, num);
        } else {
            stacks.push(token);
        }
    }
public:
    int calculate(string s) {
        stack<Token> stacks;
        int i = 0;
        Token cur_token = getNextToken(s, i);
        while (cur_token.t_type != -1) {
            if (cur_token.t_type == 0) {
                insertNumber(stacks, cur_token);
            } else {
                insertToken(stacks, cur_token);
            }
            cur_token = getNextToken(s, i);
        }
        return stacks.top().number;
    }
};

int main() {
    Solution s;
    string str = "1-(     -2)";
    cout << s.calculate(str) << endl;

}