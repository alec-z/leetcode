//
// @author Alec Zheng
// @revision first commit: 2024-04-09
// Solve this problem by greedy algorithm. order the intervals by end point.
// Then choose the leftest_end_point or leftest_end_point - 1 as one number in the containing
// set. 
// Prove:  This is a safe choose, the cue is that: the righter choice will disobey this constrains and the lefter choice
// can easy to be prove not safe. Using contradiction method to prove this. 
// key takeaways: using the cue to finger out a safe choice, then to prove it.
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;
class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        auto compared = [](const vector<int>& a, const vector<int>& b) -> bool{
            return (a[1] < b[1]) || 
            (a[1] == b[1] && a[2] < b[2]) ||
            (a[1] == b[1] && a[2] == b[2] && a[0] < b[0]);
        };
        set<vector<int>, decltype(compared)> itl_set(compared);
        set<int> tmp_set;
        for (auto & itl : intervals) {
            itl.push_back(0);
            itl_set.insert(itl);
            tmp_set.insert(itl[1]);
        }

        int total = 0;
        while (!itl_set.empty()) {
            int remove_point = (*itl_set.begin())[1];
            int first_num = (*itl_set.begin())[2];
            if (first_num == 0) {
                remove_point--;
            }
            vector<vector<int>> wait_inserts;
            auto p = itl_set.begin();
            while (p != itl_set.end()) {
                if (remove_point >= (*p)[0] && remove_point <= (*p)[1]) {
                    if ((*p)[2] == 0) {
                        wait_inserts.push_back(vector<int> {(*p)[0], (*p)[1], (*p)[2] + 1});
                    }
                    auto old = p;
                    p++;
                    itl_set.erase(old);
                } else {
                    p++;
                }
            }

            for (int i = 0; i < wait_inserts.size(); i++) {
                itl_set.insert(wait_inserts[i]);
            }
            total++;
        }
        return total;
    }
};

int main() {
    Solution s;
    vector<vector<int>> intervals {
        {7,8},
        {0,14},
        {3,11}
    };
    cout << s.intersectionSizeTwo(intervals) << endl;
}