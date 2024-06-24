#include <vector>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        vector<int> n_p(2 * 10001, -1);
        int last_p = 0;
        int total = 0;
        int diff = 0;
        int no_diff = 0;
        for (int i = 0; i < nums.size(); i++) {
            int with_i = 0;
            int cur_n = nums[i];
            if (n_p[cur_n] == -1) {
                diff++;
            }
            n_p[cur_n] = i;
            if (diff > k) {
                while (n_p[nums[last_p]] > last_p) {
                    last_p++;
                }
                n_p[nums[last_p]] = -1;
                diff--;
                last_p++;
                no_diff = 0;
            }
            if (diff == k) {
                with_i++;
                while (n_p[nums[last_p]] > last_p) {
                    last_p++;
                    with_i++;
                }
            }
            total += no_diff + with_i;
            no_diff = with_i;
        }
        return total;
    }
};

int main() {
    Solution s;
    vector<int> input{1,2,1,2,3};
    cout << s.subarraysWithKDistinct(input, 2) << endl;
}