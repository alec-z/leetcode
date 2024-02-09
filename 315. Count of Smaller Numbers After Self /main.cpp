#include <vector>
#include <iostream>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res(nums.size());
        vector<int> smallerClosest(nums.size());
        res[nums.size() - 1] = 0;
        smallerClosest[nums.size() - 1] = 0;
        for (int i = nums.size() - 2; i >=0; i--) {
            int p = i + 1;
            while (p != 0) {
                if (nums[i] >= nums[p]) {
                    
                    if (nums[i] == nums[p]) {
                        res[i] = res[p];
                        smallerClosest[i] = smallerClosest[p];
                    } else {
                        res[i] = res[p] + 1;
                        smallerClosest[i] = p;
                    }
                    break;
                } else {
                    p = smallerClosest[p];
                }
            }
            if (p == 0) {
                res[i] = 0;
                smallerClosest[i] = 0;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> a{2, 0, 1};
    for (int &c : s.countSmaller(a)) {
        cout << c << " ";
    }
    cout << endl;
}