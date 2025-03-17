#include <utility>
#include <vector>
#include <queue>
#include <functional>

using namespace std;
using Point = pair<int, int>;
class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int n = plantTime.size();
        vector<Point> ps(n);
        for (int i = 0; i < n; i++) {
            ps[i].first = plantTime[i];
            ps[i].second = growTime[i];
        }
        auto cmp = [](Point & a, Point & b) {
            return (a.second > b.second) || (a.second == b.second && a.first < b.first);
        };
        sort(ps.begin(), ps.end(), cmp);
        int res = 0;
        int max_long = 0;
        for (int i = 0; i< n; i++) {
            res += ps[i].first;
            max_long = max(max(0, max_long- ps[i].first),ps[i].second);
        }
        res += max_long;
        return res;
    }
};
int main() {
    Solution s;
    vector<int> plantTime = {1,4,3};
    vector<int> growTime = {2,3,1};
    int res = s.earliestFullBloom(plantTime, growTime);
    int a = 1;
}