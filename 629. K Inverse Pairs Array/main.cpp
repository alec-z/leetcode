#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

    
class Solution {
    
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> func(n + 1);
        vector<int> sums(k + 1, 0);
        func[1].resize(k + 1, 0);
        func[1][0] = 1;
        for (int in = 2; in <= n; in++) {
            func[in].resize(k + 1, 0);
            func[in][0] = 1;
            for (int ik = 0; ik <= k; ik++) sums[ik] = 0;
            sums[0] = 1;
            for (int ik = 1; ik <= k; ik++) 
                sums[ik] = (sums[ik - 1] + func[in - 1][ik]) % 1000000007;
            for (int ik = 1; ik <= k; ik++) {
                if (ik - in >= 0)
                    func[in][ik] += ((sums[ik] - sums[ik - in]) + 1000000007) % 1000000007;
                else 
                    func[in][ik] += (sums[ik]);
                func[in][ik] %= 1000000007;                
            }
        }
        return func[n][k];
    }
};

int main() {
    Solution s;
    cout << s.kInversePairs(2, 2) << endl;
}