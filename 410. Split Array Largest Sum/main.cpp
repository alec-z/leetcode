#include <vector>
#include <iostream>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
    map<pair<int, int>, int> fs;
    int len;
    vector<int> sums;
    int f(int i, int k) {
        auto p = fs.find(make_pair(i, k));
        if (p != fs.end()) return (*p).second;
        if (k == 1) {
            int s = sums[len] - sums[i];
            fs[make_pair(i, k)] = s;
            return s;
        }
        if (len - i < k) return -1;
        int min_sum = numeric_limits<int>::max();
        for (int j = i; j < len; j++) {
            int s = sums[j + 1] - sums[i];
            if (s > min_sum) break;
            int other_part = f(j + 1, k - 1);
            if (other_part != -1) {
                min_sum = max(s, other_part);
            }
        }
        if (min_sum == numeric_limits<int>::max()) {
            fs[make_pair(i, k)] = -1;
            return -1;
        } else {
            fs[make_pair(i, k)] = min_sum;
            return min_sum;
        }

    }
public:
    int splitArray(vector<int>& nums, int k) {
        len = nums.size();
        sums.resize(len + 1, 0);
        for (int i = 0; i < len; i++) {
            sums[i + 1] = sums[i] + nums[i];
        }
        return f(0, k);
    }

};

int main() {
    vector<int> nums {7,2,5,10,8};
    Solution s;
    cout << s.splitArray(nums, 2) << endl;
}