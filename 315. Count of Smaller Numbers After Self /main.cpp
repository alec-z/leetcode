#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int len = nums.size();
        vector<int> res(len, 0), smaller_pos(len, len);
        for (int i = len - 2; i>=0; i--) {
            int wait_check = i + 1;
            while (wait_check < len && nums[i] < nums[wait_check]) {
                wait_check = smaller_pos[wait_check];
            }
            smaller_pos[i] = wait_check;
            if (wait_check < len) {
                if (nums[i] > nums[wait_check]) {
                    res[i] = res[wait_check] + 1;
                } else {
                    res[i] = res[wait_check];
                }
               
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> a{5,2,6,1};
    for (int &c : s.countSmaller(a)) {
        cout << c << " ";
    }
    cout << endl;
}