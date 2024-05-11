#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
    set<vector<int>> n_courses;
    

public:
    int scheduleCourse(vector<vector<int>>& courses) {
        vector<vector<int>> tmp;
        for (auto & c: courses) {
            tmp.push_back({c[0], c[1] - c[0] + 1});
        }
        sort(tmp.begin(), tmp.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
        });

        for (int i = 0; i < tmp.size(); i++) {
            if (tmp[i][1] >= 1) {
                n_courses.insert(tmp[i]);
            }
        }
        
        if (n_courses.size() == 0) return 0;
        // greedy part
        int max_last_day = 0;
        for (auto & c: n_courses) {
            if (c[1] + c[0] > max_last_day) max_last_day = c[1] + c[0];
        }
        int last_day = max_last_day;
        while (!n_courses.empty()) {
            for (auto  p = n_courses.begin(); p != n_courses.end();) {
                int max_ld = -1;
                int new_last_day = min((*p)[1] - 1, last_day - (*p)[1]);
                if (new_last_day < 0) {
                    auto tmp = p;
                    p++;
                    n_courses.erase(tmp);
                } else if (new_last_day > max_ld){
                    max_ld = new_last_day;
                    p++;
                } else {
                    p++;
                }
            }
            
        }
    }
};
int main() {
    vector<vector<int>> courses {
        {9,14}
        ,{7,12},
        {1,11},
        {4,7}
    };
    Solution s;
    s.scheduleCourse(courses);

}