#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Solution {
public:
    int strongPasswordChecker(string password) {
        vector<int> cc(4, 0);
        int len = password.size();
        // 0 for uppercase, 1 for lowercase, 2 for number, 3 for other.
        vector<int> lcl;
        for (int i = 0; i < len; i++) {
            char c = password[i];
            if (c >= 'A' && c <= 'Z') cc[0] ++;
            else if (c >= 'a' && c <= 'z') cc[1] ++;
            else if (c >= '0' && c <= '9') cc[2] ++;
            else cc[3] ++;
        }
        char pre = password[0];
        int l = 1;
        for (int i = 1; i < len; i++) {
            if (password[i] == pre) {
                l++;
            } else {
                if (l >= 3)
                    lcl.push_back(l);
                pre = password[i];
                l = 1;
            }
        }
        if (l >= 3)
            lcl.push_back(l);
        int action = 0;

        // insert to break 3;
        int lcl_actions = 0;
        for (int i = 0; i < lcl.size(); i++) {
            lcl_actions += lcl[i] / 3;
        }

        if (len < 6) {
            action = lcl_actions;
            int a = action;
            for (int i = 0; i < 3 && a > 0; i++) {
                if (cc[i] == 0) {
                    cc[i]++;
                    a--;
                    len++;
                }
            }
            cc[0] += a;
            len += a;
            lcl_actions = 0;
        }

        if (len < 6) {
            action += 6 - len;
            len  = 6;
            int a = action;
            for (int i = 0; i < 3 && a > 0; i++) {
                if (cc[i] == 0) {
                    cc[i]++;
                    a--;
                }
            }
            cc[0] += a;
        }

        

        if (len > 20) {
            action = len - 20;
            len = 20;
            int a = action;
            int r = 0;
            while (a > 0 && !lcl.empty()) {
                for (auto & cl: lcl) {
                    if (cl >= 3 && cl % 3 == r && a > 0) {
                        if (a >= r + 1) {
                            a -= (r + 1);
                            cl -= (r + 1);
                        } else {
                            cl -= a;
                            a = 0;
                        }
                    }
                }
                lcl.erase(remove_if(lcl.begin(), lcl.end(), [](int i) { return i < 3;}), lcl.end());
                r = (r + 1) % 3;
            }
            lcl_actions = 0;
            for (int i = 0; i < lcl.size(); i++) {
                lcl_actions += lcl[i] / 3;
            }
            action += lcl_actions;
            a = lcl_actions;
            for (int i = 0; i < 3 && a > 0; i++) {
                if (cc[i] == 0) {
                    cc[i]++;
                    a--;
                }
            }
            lcl_actions = 0;
        }
        
        
        if (lcl_actions> 0) {
            action += lcl_actions;
            int a = lcl_actions;
            for (int i = 0; i < 3 && a > 0; i++) {
                if (cc[i] == 0) {
                    cc[i]++;
                    a--;
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            if (cc[i] == 0) {
                cc[i]++;
                action++;
            }
        }



        return action;

    }
};

int main() {
    Solution s;
    string p = "aaaB1";
    cout << s.strongPasswordChecker(p) << endl;
}