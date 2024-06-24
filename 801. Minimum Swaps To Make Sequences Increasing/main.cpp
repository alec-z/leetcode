#include <vector>
using namespace std;

class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        int p1 = 0, p2 = 0;
        while (p1 < len1 || p2 < len2) {
            while (p1 + 1 == len1 || nums1[p1] < nums1[p1 + 1]) {
                p1++;
            }

            while (p2 + 1 == len2 || nums1[p2] < nums1[p2 + 1]) {
                p2++;
            }
            
        }
        
    }
};