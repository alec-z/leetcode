#include <vector>
#include <string>
#include <limits>
#include <map>
#include <utility>
#include <iostream>
using namespace std;

#define MAX_INT numeric_limits<int>::max()

class Solution {
private:
    map<pair<int, int>, pair<int, vector<int>>> step_hash;
    vector<int> nums;
    vector<string> others;
    int try_f(int i, int positive) {
        if (i < 0) return 0;

        auto p = step_hash.find(make_pair(i, positive));
        if (p != step_hash.end()) return (*p).second.first;

        int min_steps = MAX_INT;
        vector<int> min_steps_ways;
        if (i == 0) {
            if (nums[0] > 0) {
                if (nums[0] >= positive) {
                    min_steps_ways.push_back(nums[0] - positive);
                    step_hash[make_pair(0, positive)] = make_pair(nums[0] - positive, std::move(min_steps_ways));
                    return nums[0] - positive;
                }
            } else if (nums[0] < 0) {
                if (positive == 0) {
                    min_steps_ways.push_back(nums[0]);
                    step_hash[make_pair(0, positive)] = make_pair(-nums[0], std::move(min_steps_ways));
                    return -nums[0];
                }
            }
            step_hash[make_pair(0, positive)] = make_pair(MAX_INT, std::move(min_steps_ways));
            return MAX_INT;
        }
        
        if (nums[i] > 0) {
            for (int k = 0; k <= nums[i]; k++) {
                int last_positive = positive - (nums[i] - k);
                if (last_positive < 0) continue;
                int steps = try_f(i - 1, last_positive);
                if (steps == MAX_INT) continue;
                if (steps + k < min_steps) {
                    min_steps = steps + k;
                    min_steps_ways.clear();
                    min_steps_ways.push_back(k);
                } else if (steps + k == min_steps) {
                    min_steps_ways.push_back(k);
                }
            }
        } else {
            for (int k = 0; k >= nums[i]; k--) {
                int last_positive = positive - (nums[i] - k);
                if (last_positive < 0) continue;
                int steps = try_f(i - 1,last_positive);
                if (steps == MAX_INT) continue;
                if (steps - k < min_steps) {
                    min_steps = steps - k;
                    min_steps_ways.clear();
                    min_steps_ways.push_back(k);
                } else if (steps - k == min_steps) {
                    min_steps_ways.push_back(k);
                }
            }
        }
        step_hash[make_pair(i, positive)] = make_pair(min_steps, std::move(min_steps_ways));
        return min_steps;
    }

    string numToString(int num) {
        string res;
        if (num > 0) {
            while (num > 0) {
                res.append("(");
                num --;
            }
        } else {
            while (num < 0) {
                res.append(")");
                num ++;
            }
        }
        return std::move(res);
    }

    vector<string> get_res(int i, int positive) {
        vector<string> res;
        if (i < 0) {
            res.push_back(others[0]);
        }
        if (i == 0) {
            res.push_back(others[0] + numToString(positive) + others[1]);
            return res;
        }

        const vector<int>& ways = step_hash[make_pair(i, positive)].second;
        for (int k : ways) {
            auto tmp = get_res(i - 1, positive - (nums[i] - k));
            for (int j = 0; j < tmp.size(); j++) {
                tmp[j] += (numToString(nums[i] - k));
                tmp[j] += others[i + 1];
                res.push_back(tmp[j]);
            }
        }
        return std::move(res);
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        nums.clear();
        step_hash.clear();
        others.clear();
        others.push_back("");

        int preTokenType, curTokenType = MAX_INT; // 1 for (, -1 for ), 0 for char, max_int for init.
        int preToken = 0;
        string other = "";
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                curTokenType = 1;
            } else if (s[i] == ')') {
                curTokenType = -1;
            } else {
                curTokenType = 0;
            }
            if (i > 0 && curTokenType != preTokenType) {
                if (preToken != 0) {
                    nums.push_back(preToken);
                    if (others.size() < nums.size() + 1) others.resize(nums.size() + 1);
                }
                others[nums.size()] = other;
                preToken = 0;
                other = "";
            }
            if (s[i] == ')') preToken--;
            else if (s[i] == '(') preToken++;
            else other += s[i];
            preTokenType = curTokenType;
        }
        if (preToken != 0) {
                    nums.push_back(preToken);
                    if (others.size() < nums.size() + 1) others.resize(nums.size() + 1);
        }
        others[nums.size()] = other;
        preToken = 0;
        other = "";
        try_f(nums.size() - 1, 0);
       
        return  get_res(nums.size() - 1, 0);
    }
};

int main() {
    string input = "n)(";
    Solution s;
    for (string & str: s.removeInvalidParentheses(input)) {
        cout << str << "  ";
    }
    cout << endl;
}