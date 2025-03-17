#include <functional>
#include <vector>
using namespace std;

class Seq {
  public:
    int len;
    vector<bool> s;
    int max_v;
    int min_v;
    int count;
    Seq(int len) : s(len + 1, false), len(len), max_v(0), min_v(len + 1), count(0) {}
    void refresh() {
        min_v = len + 1;
        max_v = 0;
        count = 0;
        for (int i = 1; i <= len; i++) {
            if (s[i]) {
                min_v = min(min_v, i);
                max_v = max(max_v, i);
                count++;
            }
        }
    }

    bool operator<=(const Seq &o) const {
        for (int i = len; i >= 1; i--) {
            if (s[i] && !o.s[i]) {
                return false;
            } else if (!s[i] && o.s[i]) {
                return true;
            }
        }
        return true;
    }

    int diff() {
        if  (min_v == len + 1 || max_v == 0)
            return 0;
        else {
            return max_v - min_v;
        }
    }
};

class Solution {
  public:
    int minimumIncompatibility(vector<int> &nums, int k) {
        int len = nums.size();
        vector<Seq> sol(k, Seq(len));
        int bucket_size = len / k;
        int min_sum = 1e9;
        sort(nums.begin(), nums.end(),greater<int>());
        int sum_diff = 0;

        function<void(int)> dfs = [&](int i) -> void {
            if (i == len) {
                min_sum = min(sum_diff, min_sum);
            } else {
                int num = nums[i];
                for (int j = 0; j < k; j++) {
                    int old_sum_diff = sum_diff;
                    if (sol[j].count >= bucket_size) continue;
                    if (sol[j].s[num]) continue;
                    sol[j].s[num] = true;
                    if (j > 0 && !(sol[j] <= sol[j -1])) {
                        sol[j].s[num] = false;
                        continue;
                    }
                    if (j < k - 1 && !(sol[j + 1] <= sol[j])) {
                        sol[j].s[num] = false;
                        continue;
                    }
                    sum_diff -= sol[j].diff();
                    sol[j].refresh();
                    sum_diff += sol[j].diff();
                    if (sum_diff > min_sum) {
                        sol[j].s[num] = false;
                        sol[j].refresh();
                        sum_diff = old_sum_diff;
                        continue;
                    }
                    dfs(i+1);
                    sol[j].s[num] = false;
                    sol[j].refresh();
                    sum_diff = old_sum_diff;
                }
            }
        };

        dfs(0);

        return min_sum == 1e9 ? -1 : min_sum;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1,2,1,4};
    int k = 2;
    s.minimumIncompatibility(nums, k);
}