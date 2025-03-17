#include <vector>
#include <algorithm>
#include <limits>
#include <map>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;
class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
        sort(houses.begin(), houses.end());
        int m = houses.size();

        vector<int> sums(m + 1, 0);

        for (int i = 1; i <= m; i++) {
            sums[i] = sums[i - 1] + houses[i - 1];
        }
        
        vector<vector<int> > min_dis_m(m, vector<int> (m, 0));
        for (int i = 0; i < m; i++) {
            double all = 0;
            for (int j = i; j < m; j++) {
                int min_all_distance = numeric_limits<int>::max();
                for (int k = i; k <= j; k++) {
                    int left_sum = sums[k + 1] - sums[i];
                    int right_sum = sums[j + 1] - sums[k + 1];
                    int left_len = k  - i + 1;
                    int right_len = j - k;
                    if (left_len < right_len) {
                        int d = (left_len - right_len) * (houses[k + 1] - 1) + right_sum - left_sum;
                        min_all_distance = min(min_all_distance, d);
                    } else {
                        int d = (left_len - right_len) * (houses[k]) + right_sum - left_sum;
                        min_all_distance = min(min_all_distance, d);
                    }
                }
                min_dis_m[i][j] = min_all_distance;
            }
        }
        SubSolution ss(houses,min_dis_m, k);
        return ss.try_f(m, k);
    }
    class SubSolution {
    private:
        vector<int> & houses;
        int target;
        vector<vector<int> > &min_dis_m;
        map<pair<int,int>, long> hm;
        
    public:
        SubSolution(vector<int>& houses, vector<vector<int> > &min_dis_m, int target): houses(houses), min_dis_m(min_dis_m), target(target), hm(){
        }
        long try_f(int len, int k) {
            auto p = hm.find(make_pair(len, k));
            if (p != hm.end()) {
                return p->second;
            }
            if (k == 1) {
                hm.emplace(make_pair(len, k), min_dis_m[0][len-1]);
                return min_dis_m[0][len-1];
            }
            if (k >= len) {
                hm.emplace(make_pair(len, k), 0);
                return 0;
            }
            if (len == 0) {
                hm.emplace(make_pair(len, k), 0);
                return 0;
            }            
            long total_min_dis = (long)numeric_limits<int>::max() * 2;
            for (int l_len = len - 1; l_len >= 1; l_len--) {
                total_min_dis = min(total_min_dis, try_f(l_len, k - 1) + min_dis_m[l_len][len - 1]);
            }
            hm.emplace(make_pair(len, k), total_min_dis);
            return total_min_dis;
        }
    };
};

int main() {
    Solution s;
    vector<int> houses = {15,8,9,6};
    s.minDistance(houses, 1);
}
