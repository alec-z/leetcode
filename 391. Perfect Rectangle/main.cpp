#include <vector>
#include <iostream>
#include <set>
using namespace std;

typedef struct rectangle {
    int lb_x;
    int lb_y;
    int w;
    int h;
} Rectangle;



class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {

        auto compare_y_h = [](const Rectangle & a, const Rectangle & b) {
            return (a.lb_y < b.lb_y) || 
            (a.lb_y == b.lb_y && a.h < b.h) ||
            (a.h == b.h && a.lb_x < b.lb_x) || 
            (a.lb_x == b.lb_x && a.w < b.w)
            ;
        };

        auto compare_x_w = [](const Rectangle & a, const Rectangle & b) {
            return (a.lb_x < b.lb_x) || 
            (a.lb_x == b.lb_x && a.w < b.w) ||
            (a.w == b.w && a.lb_y < b.lb_y) || 
            (a.lb_y == b.lb_y && a.h < b.h)
            ;
        };

        set<Rectangle, decltype(compare_y_h)> set_x(compare_y_h);
        set<Rectangle, decltype(compare_x_w)> set_y(compare_x_w);

        for (int i = 0; i < rectangles.size(); i++) {
            const vector<int> & r = rectangles[i];
            Rectangle *a = new Rectangle{r[0], r[1], r[2] - r[0], r[3] - r[1]};
            Rectangle *b = new Rectangle{r[0], r[1], r[2] - r[0], r[3] - r[1]};
            set_x.insert(*a);
            set_y.insert(*b);
        }
        bool c = false;
        
    }
};

int main() {
    vector<vector<int>> rectangles {
      {1,1,3,3}
      ,{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}
    };
    Solution s;
    cout <<  s.isRectangleCover(rectangles) << endl;
}