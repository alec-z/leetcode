#include <vector>
#include <algorithm>
#include <queue>

const long mod_p = 1e9 + 7;
using namespace std;

class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> engineers(n);
        for (int i = 0; i < n; i++) {
            engineers[i] = {efficiency[i], speed[i]};
        }
        sort(engineers.rbegin(), engineers.rend());
        priority_queue<long, vector<long>, greater<long>> max_k_1_s;
        long max_k_1_sum = 0;
        long res = -1;
        for (int i = n - 1; i >= 0; i--) {
            const auto & [e,s] = engineers[i];
            max_k_1_s.push(s);
            max_k_1_sum += s;
            if (max_k_1_s.size() > k) {
                max_k_1_sum -= max_k_1_s.top();
                max_k_1_s.pop();
            }
            res = max(res, e * max_k_1_sum);
        }
        
        return res % mod_p;
    }
};
int main() {
    Solution s;
    int n = 3;
    vector<int> speed {2,8,2};
    vector<int> efficiency {2,7,1};
    s.maxPerformance(n, speed, efficiency, 1);
}