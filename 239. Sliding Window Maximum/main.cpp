#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> window;
        int window_size = 0;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            window.insert(nums[i]);
            window_size++;
            if (window_size == k) {
                res.push_back(*(window.rbegin()));
                window.erase(window.find(nums[i - k + 1]));
                window_size --;
            }
        }
        return res;
    }
};