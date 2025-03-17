#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(), nums.end());
        int n = queries.size();
        vector<int> res = vector<int>(n, -1);
        for (unsigned i = 0; i < n; i++) {
            
            unsigned source = queries[i][0];
            unsigned upper = queries[i][1];
            auto be = nums.begin();
            auto en = upper_bound(nums.begin(), nums.end(), upper);
            unsigned mask = 1u << (sizeof(upper) * 8 - 1);
            unsigned pivot = 0;
            if (be == en) {
                continue;
            }
            while (mask > 0 && be + 1 < en) {
                auto n_be = be;
                auto n_en = en;
                if ((source & mask) == 0) {
                    n_be = lower_bound(be, en, pivot + mask);
                    if (n_be < n_en) {
                        pivot += mask;
                        be = n_be;
                    }
                } else {
                    n_en = lower_bound(be, en, pivot + mask);
                    if (n_en == be) {
                        pivot += mask;
                    } else if (n_en < en) {
                        en = n_en;
                    }
                    
                }
                mask >>= 1;
            }
            res[i] = source ^ *be;
        }
        return std::move(res);

    }
};

int main() {
    Solution s;
    vector<int> nums = {5,2,4,6,6,3};
    vector<vector<int>> queires = {{12,4}};
    s.maximizeXor(nums, queires);
}