#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;


class Solution {
    map<long, set<int>> num_pos_set;
    int getCombine(int pos, long target, long diff) {

        int res = 0;
        auto p = num_pos_set.find(target);
        if (p != num_pos_set.end()) {
            auto pos_p = (*p).second.upper_bound(pos);
            while (pos_p != (*p).second.end()) {
                res++;
                res += getCombine(*pos_p, target + diff, diff);
                pos_p++;
            }
        }
        return res;
    }

    int getLen(int pos, long target) {

        int res = 0;
        auto p = num_pos_set.find(target);
        if (p != num_pos_set.end()) {
            auto pos_p = (*p).second.upper_bound(pos);
            while (pos_p != (*p).second.end()) {
                res++;
                pos_p++;
            }
        }
        return res;
    }

public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        
        for (int i = 0; i < nums.size(); i++) {
            num_pos_set[nums[i]].insert(i);
        }
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                long diff = (long)nums[j] - nums[i];
                long target =  (long)nums[j] + diff;
                
                if (diff == 0)
                    res += (long)pow(2, getLen(j, target)) - 1;
                else {
                    res += getCombine(j, target, diff);
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums {0,1,2,2,2};
    cout << s.numberOfArithmeticSlices(nums) << endl;
}