#include <vector>
using namespace std;
#include <vector>
using namespace std;
class Solution {
public:
    int numWays(int steps, int arrLen) {
        vector<int> pre(steps + 2, 0);
        vector<int> next(steps + 2, 0);
        pre[0] = 1;
        vector<int> tmp;
        for (int i = 1; i <= steps; i++) {
            int top =  min(min(i, arrLen - 1), steps - i);
            for (int j = top; j >= 0; j--) {
                next[j] = pre[j];
                if (j + 1 <= arrLen - 1) {
                    next[j] += pre[j+1];
                    next[j] %= 1000000007;
                }
                if (j - 1 >= 0) { 
                    next[j] += pre[j - 1];
                    next[j] %= 1000000007;
                }
                
            }
            tmp = move(pre);
            pre= move(next);
            next = move(tmp);
        }

        return pre[0];
    }
};

int main() {
    Solution s;
    s.numWays(4, 2);
}