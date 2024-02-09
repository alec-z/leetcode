#include <vector>
#include <list>
#include <limits>
#include <iostream>

using namespace std;
class Solution {
private:
    int income(vector<int> &nums, int p, int jump) {
        int pp;
        int pre, cur = nums[p], next;
        pp = p - 1;
        if (pp == jump) pp--;
        if (pp < 0) pre = 1; else pre = nums[pp];

        pp = p + 1;
        if (pp == jump) pp++;
        if (pp == nums.size()) next = 1; else next = nums[pp];

        return pre * cur * next;
    }

public:
    int maxCoins(vector<int>& nums) {
        int result = 0;
        const int MIN_INT = std::numeric_limits<int>::min();
        list<int> list_nums;
        for (int n: nums) {
            list_nums.push_back(n);
        }
        int n = nums.size();
        for (int k = 1; k <= n; k++) {
            int max = MIN_INT;
            int max_pos = -2;
            for (int i = 0; i < nums.size(); i++) {
                int potential_income = 0;
                if (i < nums.size() - 1)
                    potential_income += income(nums, i + 1, i) - income(nums, i + 1, MIN_INT);
                if (i > 0)
                    potential_income += income(nums, i - 1, i) - income(nums, i - 1, MIN_INT);
                if (potential_income > max) {
                    max = potential_income;
                    max_pos = i;
                }
            }
            result += income(nums, max_pos, MIN_INT);
            nums.erase(next(nums.begin(), max_pos));
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> nums {1,5 };
    cout << s.maxCoins(nums) << endl;
}