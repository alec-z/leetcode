#include <iostream>
#include <vector>
using namespace std;
const unsigned long long mod_p = 1e9 + 7;
class Solution {
  public:
    int numOfWays(vector<int> &nums) { 
        return (try_f(nums) + mod_p - 1) % mod_p; }
    unsigned long long try_f(vector<int> &nums) {
        if (nums.size() == 0 || nums.size() == 1)
            return 1;
        vector<int> left, right;
        int n = nums.size();
        left.reserve(n);
        right.reserve(n);
        unsigned long long com = 1;
        unsigned long long d = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[0]) {
                left.push_back(nums[i]);
                d++;
            } else {
                right.push_back(nums[i]);
            }
        }
        com = NCR(n - 1, d);
        return (try_f(left) * ((try_f(right) * com) % mod_p)) % mod_p;
    }
    unsigned long long NCR(unsigned long long n, unsigned long long r) {
        if (r == 0)
            return 1;
        if (r > n / 2)
            return NCR(n, n - r);

        unsigned long long res = 1;

        for (long k = 1; k <= r; ++k) {
            res *= n - k + 1;
            res /= k;
            res %= mod_p;
        }

        return res;
    }
};

int main() {
    vector<int> nums{30,11,46,3,29,22,37,32,13,49,48,16,40,8,24,44,9,39,25,21,41,26,43,19,47,7,10,31,45,4,35,14,20,23,15,17,38,2,6,18,5,33,27,36,42,28,12,34,1};
    Solution s;
    cout << s.numOfWays(nums);
}