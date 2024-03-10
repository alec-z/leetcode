#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;


class SummaryRanges {
    set<pair<int, int>> set;
    public:
    SummaryRanges() {
        

    }

    void addNum(int value) {
        pair<int, int> target = make_pair(value, value);
        bool merged = false;

        auto p = set.lower_bound(target);
        auto pre = p;
        if (set.empty()) {
            set.insert(target);
            return;
        }
        if (p != set.begin()) {
            pre --; // p maybe not exist;
            if ((*pre).second + 1 >= target.first) {
                target.first = (*pre).first;
                if (target.second < (*pre).second) {
                    target.second = (*pre).second;
                }
                set.erase(pre);
                p = set.lower_bound(target);
            }
        }
        if (p != set.end()) {    
            if ((*p).first <= target.second + 1) {
                target.second = (*p).second;
                set.erase(p);
            }
        }

        set.insert(target);
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> res;
        for (auto p : set) {
            res.push_back({p.first, p.second});
        }
        return res;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */

int main() {

}