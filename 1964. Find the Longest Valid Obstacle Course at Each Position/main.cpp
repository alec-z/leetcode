#include <utility>
#include <vector>
#include <map>
using namespace std;
class Solution {
private:
    map<int, int> le_than_longest;
    pair<int, int> floor(int k) {
        auto it = le_than_longest.upper_bound(k);
        if (it == le_than_longest.begin()) {
            return make_pair(-1, 0);
        } else {
            it--;
            return *it;
        }
    }
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int len = obstacles.size();
        vector<int> res(len, 1);
        for (int i = 0; i < len; i++) {
            auto find = floor(obstacles[i]);
            res[i] += find.second;
            le_than_longest[obstacles[i]] = res[i];
            auto greater_it = le_than_longest.upper_bound(obstacles[i]);
            if (greater_it != le_than_longest.end() && greater_it->second == res[i]) {
                le_than_longest.erase(greater_it);
            }
        }
        return res;
    }
};