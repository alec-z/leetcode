#include <vector>
#include <list>
#include <limits>
#include <iostream>
#include <map>

using namespace std;

struct Interval {
    int begin;
    int end;
    bool operator<(const Interval &o) const{
        return (begin < o.begin) ||
        (begin == o.begin && end < o.end);
    }
};

class Solution {
private:
    int f(map<Interval, int> &r_map, vector<int> &nums, Interval itl) {
        auto p = r_map.find(itl);
        if (p != r_map.end()) { return (*p).second;}
        if (itl.begin > itl.end) {return 0;}
        int max = std::numeric_limits<int>::min(), cur;
        for (int last = itl.begin; last <= itl.end; last++) {
            Interval right = itl;
            right.begin = last + 1;
            Interval left = itl;
            left.end = last - 1;

            if (last == itl.begin) {
                cur = f(r_map, nums, right) + income(nums, last, itl);
            } else if (last == itl.end) {
                cur = f(r_map, nums, left) + income(nums, last, itl);
            } else {
                cur = f(r_map, nums, left) + f(r_map, nums, right) + income(nums, last, itl);
            }
            if (cur > max) {
                max = cur;
            }
        }
        r_map[itl] = max;
        return max;
        

    }
    int income(vector<int> &nums, int last, Interval itl) {
        return nums[itl.begin - 1] * nums[last] * nums[itl.end + 1];
    }

public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        map<Interval, int> r_map;
        Interval first {1, (int)nums.size() - 2};
        return f(r_map, nums, first);
    }
};

int main() {
    Solution s;
    vector<int> nums {3,1,5,8};
    cout << s.maxCoins(nums) << endl;
}