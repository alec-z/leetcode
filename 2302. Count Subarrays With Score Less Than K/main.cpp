#include <vector>
#include <functional>
using namespace std;
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        vector<long long> sums(n + 1, 0);
        for (int i = 1; i <= n; i++) sums[i] = (nums[i - 1]+ sums[i - 1]);

        function<long long (int, int)> try_f = [&](int be, int en) -> long long {
            if (be > en) {
                return 0;
            }
            if (be == en) {
                if (nums[be] < k) {
                    return 1;
                } else {
                    return 0;
                }
            }
            int mid = (be + en) / 2;
            long long left = try_f(be, mid);
            long long right = try_f(mid + 1, en);
            int p_l = mid;
            long long s_l = 0;
            int p_r =  en;
            long long  mids = 0;
            long long res = 0;
            while (p_l >= be && p_r >= mid + 1) {
                s_l += nums[p_l];
                if (s_l * (mid - p_l + 1) < k) {
                    while (p_r >= mid + 1) {
                        long long s_a = sums[p_r + 1] - sums[p_l];
                        if (s_a * (p_r - p_l + 1) < k) {
                            mids += p_r - mid;
                            break;
                        } else {
                            p_r--;
                        }
                    }
                } else {
                    break;
                }
                p_l--;
            }
            return left + right + mids;
        };
        return try_f(0, n - 1);
    }
};

int main() {
    vector<int> nums = {2,1,4,3,5};
    int k = 10;
    Solution s;
    int sum = s.countSubarrays(nums, k);
    return sum;
}