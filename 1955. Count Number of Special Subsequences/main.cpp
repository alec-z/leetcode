#include <vector>
using namespace std;

class Solution {
public:
    using ll = long long;
    const ll mod_p = 1e9 + 7;
    int countSpecialSubsequences(vector<int>& nums) {
        ll s0 = 0, s1 = 0, s2 = 0;
        int n = nums.size(); 
        for (int i = 0; i < n; i++) {
            int c = nums[i];
            switch(c) {
                case 0:
                s0 += s0 + 1;
                s0 %= mod_p;
                break;
                case 1:
                s1 += s0 + s1;
                s1 %= mod_p;
                break;
                case 2:
                s2 += s1 + s2;
                s2 %= mod_p;
                break;
            }
        }
        return s2;
    }
};

int main() {
    vector<int> nums = {0,1,2,2};
    Solution s;
    s.countSpecialSubsequences(nums);

}