#include <numeric>
#include <vector>
using namespace std;
class Solution {
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        if (sum1 < sum2) {
            swap(nums1, nums2);
            swap(sum1, sum2);
        }
        int more1 = 0;
        int max_more1 = 0;
        int more2 = 0;
        int max_more2 = 0;
        for (int i = 0; i < n; i++) {
            if (nums2[i] > nums1[i]) {
                more1 += nums2[i] - nums1[i];

                if (more2 + nums1[i] - nums2[i] > 0) {
                    more2 = more2 + nums1[i] - nums2[i];
                } else {
                    more2 = 0;
                }

            } else {
                if (more1 + nums2[i] - nums1[i] > 0) {
                    more1 = more1 + nums2[i] - nums1[i];
                } else {
                    more1 = 0;
                }
                
                more2 += nums1[i] - nums2[i];
            }
            max_more1 = max(max_more1, more1);
            max_more2 = max(max_more2, more2);
        }
        return max(sum1 + max_more1, sum2+max_more2);
        
    }
};

int main() {
    vector<int> nums1 = {28,34,38,14,30,31,23,7,28,3};
    vector<int> nums2 = {42,35,7,6,24,30,14,21,20,34};
    Solution s;
    s.maximumsSplicedArray(nums1, nums2);

}