#include <vector>
#include <limits>
using namespace std;
const int MIN_INT = numeric_limits<int>::min() + 1e6;
class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size();
        int l2 = nums2.size();
        vector<vector<int> > max_dot(l1 + 1, vector<int> (l2 + 1, MIN_INT));


        
        for (int i = 1; i <= l1; i++) {
            for (int j = 1; j <= l2; j++) {
                max_dot[i][j] = max(max_dot[i][j], max_dot[i - 1][j - 1] + nums1[i - 1] * nums2[j - 1]);
                max_dot[i][j] = max(max_dot[i][j], nums1[i - 1] * nums2[j - 1]);
                max_dot[i][j] = max(max_dot[i][j], max_dot[i][j - 1]);
                max_dot[i][j] = max(max_dot[i][j], max_dot[i- 1][j]);
                max_dot[i][j] = max(max_dot[i][j], max_dot[i - 1][j - 1]);
            }
        }
        return max_dot[l1][l2];
    }
};
