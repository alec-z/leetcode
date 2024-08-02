#include <vector>
using namespace std;
const int MAX_INT = 65536;
class Solution {
public:
    int countTriplets(vector<int>& nums) {
        vector<int> t_n(MAX_INT, 0);
        for (int i = 0; i < nums.size(); i++) {
            for (int t = 0; t < MAX_INT; t++) {
                if ((nums[i] & t) == 0) {
                    t_n[t]++;
                }
            }
        }
        int res = 0;
        for (int i=0; i < nums.size(); i++) {
            for (int j=0; j < nums.size(); j++) {
                unsigned short tmp = ((unsigned short)nums[i] & (unsigned short)nums[j]);
                res += t_n[tmp];
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums {2,1,3};
    s.countTriplets(nums);

}