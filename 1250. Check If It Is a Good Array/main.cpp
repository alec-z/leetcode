#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
class Solution {
    set<int> get_prim_set(int a) {
        int a_sqrt = sqrt(a);
        set<int> res;
        bool found = false;
        for (int i = 2; i <= a_sqrt && a > 1; i++, found = false) {
            while (a % i == 0) {
                a = a / i;
                found = true;
            }
            if (found)
                res.insert(i);
        }
        if (a > 1) {
            res.insert(a);
        }
        return move(res);
    }

    bool check_update(set<int> & all_set, int n) {
        bool found = false;
        for (auto i = all_set.begin(); i != all_set.end(); ) {
            if (n % (*i) == 0) {
                found = true;
                i++;
            } else {
                i = all_set.erase(i);
            }
        }
        return !found;
        
    }


    
public:
    bool isGoodArray(vector<int>& nums) {
        set<int> all_set = get_prim_set(nums[0]);
        for (auto n: nums) {
            if (n == 1) return true;
            if (check_update(all_set, n))
                return true;
        }
        return false;
    }
};

int main() {
    vector<int> nums {6,10,15};
    Solution s;
    cout << s.isGoodArray(nums);
}