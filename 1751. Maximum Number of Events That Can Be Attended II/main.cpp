#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort(events.begin(), events.end(), [](const auto & a, const auto &b) {
            return a[1] < b[1]; 
        });
        vector<vector<int>> dp(events.size(), vector<int>(k + 1, 0));
        auto comp = [](const vector<int> & a, const vector<int> &b) {
            return a[1] < b[1]; 
        };
        vector<int> temp(3, -1);
        for (int j = 1; j <= k; j++) {
            for (int i = 0; i < events.size(); i++) {                
                    temp[1] = events[i][0] - 1;
                    auto p = upper_bound(events.begin(), events.begin() + i, temp, comp);
                    if (i > 0) {
                        dp[i][j] = dp[i - 1][j];
                    }
                    if (p != events.begin()) {
                        p--;
                        int far = p - events.begin();
                        dp[i][j] = max(dp[i][j], dp[far][j - 1] + events[i][2]);
                    } else {
                        dp[i][j] = max(dp[i][j], events[i][2]);
                    }
            }
        }
        return dp[events.size() - 1][k];
    }
};
int main() {
    Solution s;
    vector<vector<int>> events = {
        {1,2,4},{3,4,3},{2,3,1}
    };
    int k = 2;
    s.maxValue(events, k);

}