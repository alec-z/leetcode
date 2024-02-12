#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <functional>

using namespace std;
struct Event {
    int type; // 0 for begin point, 1 for end point;
    int x;
    int height;
};
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<Event> event_list;
        for (int i = 0; i < buildings.size(); i++) {
            event_list.push_back(Event {0, buildings[i][0], buildings[i][2]});
            event_list.push_back(Event {1, buildings[i][1], buildings[i][2]});
        }
        sort(event_list.begin(), event_list.end(), [](const Event a, const Event b) { return a.x < b.x;});

        //max height queue.
        vector<vector<int>> res;
        int i = 0;
        multiset<int> heights;
        for (int i = 0; i < event_list.size();) {
            int cur_x = event_list[i].x;
            int top = heights.empty()? 0 : *(heights.rbegin());
            while (i < event_list.size() && event_list[i].x == cur_x) {
                if (event_list[i].type == 0) {
                    heights.insert(event_list[i].height);
                } else {
                    heights.erase(heights.find(event_list[i].height));
                }
                i++;
            }
            int new_top = heights.empty()? 0 : *(heights.rbegin());
            if (top != new_top) {
                res.push_back(vector<int> {cur_x, new_top});
            }
        }
        return res;
        
    }
};

int main() {
    vector<vector<int>> buildings {{0,3,3},{1,5,3},{2,4,3},{3,7,3}};
    Solution s;
    vector<vector<int>>  res = s.getSkyline(buildings);
    int c = 2;
    
}