#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

using namespace std;
// greedy based


class Solution {
private:
    vector<int> max_number(vector<int> & nums, int k) {
        vector<int> res;
        int start = 0;
        int nums_limit = nums.size() - (k - 1);
        int pos = 0;
        int max_digit = -1;
        int i;
        int all_possible_max_digit = 9;
        while (k > 0) {
            for (i = start; i < nums_limit; i++) {
                if (nums[i] > max_digit) {
                    max_digit = nums[i];
                }
                if (max_digit == all_possible_max_digit) break;
            }
            for (i = start; i < nums_limit; i++) {
                if (nums[i] == max_digit) {
                    break;
                }
            }
            res.push_back(max_digit);
            start = i + 1;
            k--;
            all_possible_max_digit = max(nums[nums_limit++], max_digit);
            max_digit = -1;
        }
        return res;
    }
    vector<int> merge(const vector<int> & nums1, const vector<int> & nums2) {
        vector<int> res;
        int i = 0, j = 0;
        while (i < nums1.size() || j < nums2.size()) {
            if (i == nums1.size()) res.push_back(nums2[j++]);
            else if (j == nums2.size()) res.push_back(nums1[i++]);
            else if (nums2[j] > nums1[i]) res.push_back(nums2[j++]);
            else res.push_back(nums1[i++]);
        }
        return res;
    }
    bool less(const vector<int> & v1, const vector<int> & v2) const {
        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] < v2[i]) {
                return true;
            } else if (v1[i] > v2[i]) {
                return false;
            }
        }
        return false;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> max_res(k, 0);
        for (int i = 0; i <=k; i++) {
            if (i > nums1.size() || k - i > nums2.size()) {
                continue;
            }
            const vector<int> & part1 = max_number(nums1, i);
            const vector<int> & part2 = max_number(nums2, k - i);
            vector<int> all_part = merge(part1, part2);
            if (less(max_res, all_part)) {
                max_res = all_part;
            }
        }
        return max_res;
    }
};

int main() {
    Solution s;
    vector<int> nums1 {3,4,6,5};
    vector<int> nums2 {9,1,2,5,8,3};
    int k = 5;
    for (int d : s.maxNumber(nums1, nums2, k)) {
        cout << d << " ";
    }
    cout << endl;
}