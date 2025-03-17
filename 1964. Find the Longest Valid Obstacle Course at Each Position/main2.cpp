/*
 * merged dp tree
 */
#include <vector>
#include <functional>
using namespace std;
class Solution {
private:
    
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int len = obstacles.size();
        vector<int> res(len, 0);
        vector<int> sub(len, 0);
        int sub_len = 0;
        function<int(int)> b_find = [&](int k) -> int {
            int be = 0;
            int en = sub_len;
            int mid;
            while (be < en) {
                mid = (be + en) / 2;
                if (k < sub[mid]) {
                    en = mid;
                } else {
                    be = mid + 1;
                }
            }
            return be;

        };
        for (int i = 0; i < len; i++) {
            int p = b_find(obstacles[i]);
            res[i] = p + 1;
            sub[p] = obstacles[i];
            if (p == sub_len) sub_len++;
        }
        return res;
    }
};

int main() {
    vector<int> input = {1,2,3,2};
    Solution s;
    s.longestObstacleCourseAtEachPosition(input);
}