/*
 * merged binary index tree
 */
#include <vector>
using namespace std;
class Solution {
    vector<int> bit;
private:
    const int MAX_N = 1e7;
    int get(int i) {
        int res = 0;
        while (i > 0) {
            res = max(res, bit[i]);
            i -= (i & -i);
        }
        return res;
    }
    void put(int i, int l) {
        while (i <= MAX_N) {
            l = max(bit[i], l);
            bit[i] = l;
            i += (i & -i);
        }
    }
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        bit.resize(MAX_N + 1, 0);
        int len = obstacles.size();
        vector<int> res(len, 0);
        for (int i = 0; i < len; i++) {
            int o = obstacles[i];
            res[i] = get(o) + 1;
            put(o, res[i]);
        }
        return res;
    }
};

int main() {
    vector<int> input = {1,2,3,2};
    Solution s;
    s.longestObstacleCourseAtEachPosition(input);
}