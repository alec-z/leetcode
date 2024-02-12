#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        multiset<int> window;
        int window_size = 0;
        window.insert(nums[0]);
        window_size ++;
        for (int i = 1; i < nums.size(); i++) {
            int n = nums[i];
            int lower = n - valueDiff;
            int upper = n + valueDiff;
            auto p = window.lower_bound(lower);
            if (p != window.end() && (*p) <= upper) {
                return true;
            }
            window.insert(nums[i]);
            window_size ++;
            if (window_size == indexDiff + 1) {
                window.erase(window.find(nums[i - indexDiff]));
                window_size --;
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> nums {1,5,9,1,5,9};
    int indexDiff = 2;
    int valueDiff = 3;
    cout << s.containsNearbyAlmostDuplicate(nums, indexDiff, valueDiff) << endl;
}