#include <vector>
#include <iostream>
#include <set>
using namespace std;

typedef struct rectangle {
    int lb_x;
    int lb_y;
    int rt_x;
    int rt_y;
} Rectangle;



class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {

        auto compare_rt_x = [](const Rectangle & a, const Rectangle & b) {
            return (a.lb_x < b.lb_x) || 
            (a.lb_x == b.lb_x && a.lb_y < b.lb_y) ||
            (a.lb_y == b.lb_y && a.rt_x < b.rt_x) ||
            (a.rt_x == b.rt_x && a.rt_y < b.rt_y);
        };

        auto compare_rt_y = [](const Rectangle & a, const Rectangle & b) {
            return (a.lb_x < b.lb_x) || 
            (a.lb_x == b.lb_x && a.lb_y < b.lb_y) ||
            (a.lb_y == b.lb_y && a.rt_y < b.rt_y) ||
            (a.rt_y == b.rt_y && a.rt_x < b.rt_x);
        };

        set<Rectangle, decltype(compare_rt_x)> set_rt_x(compare_rt_x);
        set<Rectangle, decltype(compare_rt_y)> set_rt_y(compare_rt_y);
        for (int i = 0; i < rectangles.size(); i++) {
            const vector<int> & r = rectangles[i];
            
            set_rt_x.insert({r[0], r[1], r[2], r[3]});
            set_rt_y.insert({r[0], r[1], r[2], r[3]});
        }
        if (set_rt_x.size() != rectangles.size()) return false;

        while (!set_rt_x.empty()) {
            if (set_rt_x.size() == 1) return true;
            bool found = false;
            Rectangle first, second, merged;

            for (Rectangle e: set_rt_x) {
                Rectangle tmp;
                first.lb_x = e.lb_x;
                first.lb_y = e.lb_y;
                first.rt_x = e.rt_x;
                first.rt_y = e.rt_y;

                // find righter rect
                tmp.lb_x = e.rt_x;
                tmp.lb_y = e.lb_y;
                tmp.rt_y = e.rt_y;
                tmp.rt_x = e.rt_x + 1;
                auto p_rt_y = set_rt_y.lower_bound(tmp);
                if (p_rt_y != set_rt_y.end()) {
                    Rectangle r_rt_y = *p_rt_y;
                    if (tmp.lb_x == (r_rt_y).lb_x && tmp.lb_y == (r_rt_y).lb_y && tmp.rt_y == (r_rt_y).rt_y) {
                        
                        merged.lb_x = e.lb_x;
                        merged.lb_y = e.lb_y;
                        merged.rt_x = (r_rt_y).rt_x;
                        merged.rt_y = (r_rt_y).rt_y;
                        
                        second.lb_x = r_rt_y.lb_x;
                        second.lb_y = r_rt_y.lb_y;
                        second.rt_x = r_rt_y.rt_x;
                        second.rt_y = r_rt_y.rt_y;

                        found = true;

                        break;
                    }
                }

                // find toper rect
                tmp.lb_x = e.lb_x;
                tmp.lb_y = e.rt_y;
                tmp.rt_x = e.rt_x;
                tmp.rt_y = e.rt_y + 1;
                auto p_rt_x = set_rt_x.lower_bound(tmp);
                if (p_rt_x != set_rt_x.end()) {
                    Rectangle r_rt_x = (*p_rt_x);
                    if (tmp.lb_x == (r_rt_x).lb_x && tmp.lb_y == (r_rt_x).lb_y && tmp.rt_x == (r_rt_x).rt_x) {
                        merged.lb_x = e.lb_x;
                        merged.lb_y = e.lb_y;
                        merged.rt_x = (r_rt_x).rt_x;
                        merged.rt_y = (r_rt_x).rt_y;

                        second.lb_x = r_rt_x.lb_x;
                        second.lb_y = r_rt_x.lb_y;
                        second.rt_x = r_rt_x.rt_x;
                        second.rt_y = r_rt_x.rt_y;

                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                return false;
            } else {
                set_rt_x.erase(first);
                set_rt_x.erase(second);
                set_rt_x.insert(merged);

                set_rt_y.erase(first);
                set_rt_y.erase(second);
                set_rt_y.insert(merged);
            }
        }
        return true;
    }
};

int main() {
    vector<vector<int>> rectangles {
       {0,1,3,3},{0,3,2,5},{0,0,2,1},{2,4,3,5},{2,0,3,1},{2,3,3,4}
    };
    Solution s;
    cout <<  s.isRectangleCover(rectangles) << endl;
}