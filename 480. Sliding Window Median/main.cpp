#include <vector>
#include <iostream>
#include <set>
using namespace std;


class Solution {
    int position_to(multiset<int>::iterator p, multiset<int>::iterator target, multiset<int>::iterator end) {
        if (p == target) return 0;
        if (*p < *target) return -1;
        if (*p > *target) return 1;
        auto tmp = p;
        while (tmp != end && tmp != target && *tmp == *target) {
            tmp++;
        }
        if (tmp == target) return -1;
        return 1;
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int> window(nums.begin(), nums.begin() + k);
        multiset<int>::iterator p_left = window.begin(), p_right;
        vector<double> res;
        if (k == 1) {
            for (int i = 0; i < nums.size(); i++) res.push_back(nums[i]);
            return res;
        }
        for (int i = 0; i < (k - 1) / 2; i ++) {
            p_left++;
        }
        p_right = p_left;
        if (k % 2 == 0) {
            p_right++;
        }
        res.push_back(((double)*p_left + *p_right) / 2);
        for (int i = 1; i <= nums.size() - k; i++) {
            int removed = nums[i - 1];
            auto removed_p = window.find(removed);
            
            if (p_left == p_right) {
                int compared = position_to(removed_p, p_left, window.end());
                if (compared < 0) {
                    window.erase(removed_p);
                    p_right++;
                } else if (compared > 0) {
                    window.erase(removed_p);
                    p_left--;
                } else {
                    p_left--;
                    p_right++;
                    window.erase(removed_p);
                }
            } else {
                int compared = position_to(removed_p, p_left, window.end());
                if (compared <= 0) {
                    p_left++;
                    window.erase(removed_p);
                } else {
                    p_right--;
                    window.erase(removed_p);
                }
            }
            int added = nums[i + k - 1];
            auto insert_p  = window.insert(added);
            if (p_left == p_right) {
                int compared = position_to(insert_p, p_left, window.end());
                if (compared < 0) p_left--;
                else if (compared > 0) p_right++;
            } else {
                int compared = position_to(insert_p, p_left, window.end());
                if (compared < 0) {
                    p_right--;
                } else {
                    int compared2 = position_to(insert_p, p_right, window.end());
                    if (compared2 < 0) {
                        p_left++;
                        p_right--;
                    } else {
                        p_left++;
                    }
                }
            }
            res.push_back(((double)*p_left + *p_right) / 2);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums{7,0,3,9,9,9,1,7,2,3};
    int k = 6;
    auto res = s.medianSlidingWindow(nums, k);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}