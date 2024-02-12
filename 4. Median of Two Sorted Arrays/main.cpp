#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


class Solution {
private:
    int find_kth(vector<int> & nums_long, int lo_long, int hi_long, vector<int> & nums_short, int lo_short, int hi_short, int k) {
        // first
       
        if (hi_long - lo_long < hi_short - lo_short) {
            swap(nums_long, nums_short);
            swap(lo_long, lo_short);
            swap(hi_long, hi_short);
        }
        if (lo_long > hi_long) return -1;
        int mid_long = (lo_long + hi_long) / 2;
        int pivot = nums_long[mid_long];

        int be = lo_short, en = hi_short, res = lo_short - 1;
        
        while (be <= en) {
            int mid = (be + en) / 2;
            if (nums_short[mid] == pivot) {
                res = mid;
                break;
            } else if (nums_short[mid] < pivot) {
                be = mid + 1;
                if (be > en) {
                    res = mid;
                    break;
                }
            } else {
                en = mid - 1;
                if (be > en) {
                    res = en;
                    break;
                }
            }
        }
        int less_long = mid_long -lo_long;
        int less_short = res - lo_short + 1;

        if (k == less_long + less_short) {
            return pivot;
        } else if (k < less_long + less_short) {
            return find_kth(nums_long, lo_long, mid_long - 1, nums_short, lo_short, res, k);
        } else {
            return find_kth(nums_long, mid_long + 1, hi_long, nums_short, res + 1, hi_short, k - (less_long + less_short + 1));
        }
    }

public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if ((len1 + len2) % 2 == 1) {
            return find_kth(nums1, 0, len1 - 1, nums2, 0, len2 -1, (len1 + len2) / 2);
        } else {
            double first = (double)find_kth(nums1, 0, nums1.size() - 1, nums2, 0, nums2.size() -1, (len1 + len2 - 1) / 2);
            double second = find_kth(nums1, 0, nums1.size() - 1, nums2, 0, nums2.size() -1, (len1 + len2) / 2);
            return (first + second) / 2; 
        }
    }
};

int main() {
    vector<int> nums1;
    vector<int> nums2 {2,3};
    Solution s;
    cout << s.findMedianSortedArrays(nums1, nums2) << endl;
}