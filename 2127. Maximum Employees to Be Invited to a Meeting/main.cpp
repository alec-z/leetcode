#include <utility>
#include <vector>
#include <functional>
using namespace std;

using Point = pair<int, int>;
class Solution {

public:
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        vector<int> visited(n, -1);
        vector<int> circle_len(n, 0);

        for (int i = 0; i < n; i++) {
            if (visited[i] == -1) {
                visited[i] = i;
                int p = favorite[i];
                while (visited[p] == -1) {
                    visited[p] = i;
                    p = favorite[p];
                }
                if (visited[p] != i) {
                    continue;
                } else {
                    int pp = p;
                    int len = 0;
                    do {
                        pp = favorite[pp];
                        len++;
                    } while (pp != p);
                    pp = p;
                    do {
                        pp = favorite[pp];
                        circle_len[pp] = len;
                    } while (pp != p);
                }
            }
        }
        Point zero = make_pair(-1, 0);
        vector<Point> dp(n, zero);
        function<Point(int i)> f_dp = [&](int i) -> Point {
            if (dp[i].first != -1) return dp[i];
            if (circle_len[i] > 2) {
                return (dp[i] = make_pair(-2, 0));
            } else if (circle_len[i] == 2) {
                return (dp[i] = make_pair(i, 1));
            }
            int p = favorite[i];
            auto p_res = f_dp(p);
            if (p_res.first == -2) {
                return (dp[i] = make_pair(-2, 0));
            } else {
                return (dp[i] = make_pair(p_res.first, p_res.second + 1));
            }
        };

  
        for (int i = 0; i < n; i++) {
            f_dp(i);
        }
        int max_i = 0;
        vector<int> max_half_len(n, 0);
        for (int i = 0; i < n; i++) {
            if (dp[i].first == -2 && circle_len[i] > 2) {
                max_i = max(max_i, circle_len[i]);
            } else if (dp[i].first >= 0) {
                max_half_len[dp[i].first] = max(max_half_len[dp[i].first], dp[i].second);
            }
        }
        int all = 0;
        for (int i = 0; i < n; i++) {
            all += max_half_len[i];
        }
        return max(max_i, all);
    }
     
};

int main() {
    Solution s;
    vector<int> input = {3,0,1,4,1};
    int res = s.maximumInvitations(input);
}