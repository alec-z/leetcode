#include <vector>
#include <limits>
using namespace std;
const int MAX_INT = numeric_limits<int>::max();
class Solution {
  public:
    vector<int> canSeePersonsCount(vector<int> &heights) {
        int n = heights.size();
        vector<int> res(n, 0);
        vector<int> right_close_ge(n, n);
        for (int i = n - 2; i >= 0; i--) {
            int j = i + 1;
            do  {
                if (heights[i] > heights[j]) {
                    res[i]++;
                    j = right_close_ge[j];
                }
                else break;
            } while (j < n);
            right_close_ge[i] = j;
        }

        for (int i = n - 2; i >= 0; i--) {
            if (right_close_ge[i] != n) {
                res[i]++;
            }
        }
        return res;
    }
};

int main() {
    vector<int> heights = {10,6,8,5,11,9};
    Solution s;
    auto res = s.canSeePersonsCount(heights);
    res[1];
}