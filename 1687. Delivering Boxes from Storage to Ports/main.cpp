#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        long long len = boxes.size();
        
        vector<long long> sum_weight(len + 1, 0);
        for (long long i = 1; i <= len; i++) {
            sum_weight[i] = boxes[i - 1][1] + sum_weight[i - 1];
            
        }
        vector<long long> same_port(len, 0);
        vector<long long> port_count(len, 0);
        for (long long i = 0; i < len; i++) {
            if (i > 0) {
                if (boxes[i][0] == boxes[i - 1][0]) {
                    same_port[i] = same_port[i - 1];
                    port_count[i] = port_count[i - 1];
                } else {
                    same_port[i] = i;
                    port_count[i] = port_count[i - 1] + 1;
                }
            }
            else {
                same_port[0] = 0;
                port_count[0] = 1;
            }
        }

        function<long long(long long, long long)> get_ports = [&](long long i, long long j)->long long {
            if (i >= j) return 0;
            if (same_port[i] > 0) {
                return port_count[j - 1] - port_count[same_port[i] - 1];
            } else {
                return port_count[j - 1];
            }
        };
        const long long MAX_N = 1e9;
        vector<long long> dp(len, MAX_N);

        auto p = upper_bound(sum_weight.begin(), sum_weight.end(), maxWeight);
        p--;
        long long p_i = (p - sum_weight.begin() - 1);
        long long upper = min<long long>(p_i, maxBoxes - 1);
        dp[upper] = min(dp[upper], get_ports(0, upper + 1) + 1);
        long long pos = same_port[upper] - 1;
        if (pos >= 0) {
            dp[pos] = min(dp[pos], get_ports(0, pos + 1) + 1);
        }


        for (long long i = 0; i < len - 1; i++) {
            if (dp[i] != MAX_N) {
                long long weight = sum_weight[i + 1] + maxWeight;
                auto p = upper_bound(sum_weight.begin() + i, sum_weight.end(), weight);
                p--;
                long long p_i = (p - sum_weight.begin() - 1);
                long long upper = min(p_i, i + maxBoxes);
               
                dp[upper] = min(dp[upper], dp[i] + get_ports(i + 1, upper + 1) + 1);
                
                long long pos = same_port[upper] - 1;
                if (pos >= 0 && pos > i) {
                    dp[pos] = min(dp[pos], dp[i] + get_ports(i + 1, pos + 1) + 1);
                }
            }
                    
        }
        return dp[len - 1];
    }
};

long long main() {
    Solution s;
    vector<vector<int>> boxes = {{1,1},{2,1},{1,1}};
    int portsCount = 3, maxBoxes = 3, maxWeight = 6;
    s.boxDelivering(boxes, portsCount,  maxBoxes, maxWeight);
}