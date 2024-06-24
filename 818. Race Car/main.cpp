#include <map>
#include <deque>
#include <cmath>
using namespace std;



class Solution {
public:
    int racecar(int target) {
        map<pair<int,int>, int> dis_map;
        deque<pair<int,int>> que;
        que.emplace_back(make_pair(0, 1));
        dis_map[make_pair(0,1)] = 0;
        const int MAX_RANGE = 2 * 10000 + 1;
        while (!que.empty()) {
            auto p = que.front();
            int dis = dis_map[p];
            que.pop_front();
            int a_p = p.first + p.second;
            int a_s = p.second * 2;
            auto a = make_pair(a_p, a_s);
            if (dis_map.find(a) == dis_map.end() && abs(a_p) < MAX_RANGE && abs(a_s) < MAX_RANGE) {
                dis_map[a] = dis + 1;
                que.emplace_back(a);
                if (a_p == target)
                    return dis + 1; 
            }
            int r_p = p.first ;
            int r_s = p.second > 0 ? -1 : 1;
            auto r = make_pair(r_p, r_s);
            if (dis_map.find(r) == dis_map.end() && abs(r_p) < MAX_RANGE && abs(r_s) < MAX_RANGE ) {
                dis_map[r] = dis + 1;
                que.emplace_back(r);
            }
        }
        return -1;
    }
};