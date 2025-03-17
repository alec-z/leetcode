#include <vector>
using namespace std;
const long mod_p = 1e9 + 7;
class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size();
        int l2 = nums2.size();
        long sp1 = 0, sp2 = 0, p1 = 0, p2 = 0;;
        long res = 0;
        while (p1 < l1 && p2 < l2) {
            while (p1 < l1 && p2 < l2 && nums1[p1] < nums2[p2]) {
                sp1 += nums1[p1];
                p1++;
            }
            while (p1 < l1 && p2 < l2 && nums1[p1] > nums2[p2]) {
                sp2 += nums2[p2];
                p2++;
            }
            if (p1 < l1 && p2 < l2 && nums1[p1] == nums2[p2]) {
                res += max(sp1, sp2) + nums1[p1];
                res %= mod_p;
                sp1 = 0;
                sp2 = 0;
                p1++;
                p2++;
            }
        }
        while (p1 < l1) {
                sp1 += nums1[p1];
                p1++;
            }
        while (p2 < l2) {
            sp2 += nums2[p2];
            p2++;
        }
        res += max(sp1, sp2);
        res %= mod_p;
        return res;
    }
};

int main() {
    vector<int> nums1 = {2,4,5,8,10};
    vector<int> nums2 = {4,6,8,9};
    Solution s;
    s.maxSum(nums1, nums2);
}