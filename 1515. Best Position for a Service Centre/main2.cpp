#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
typedef pair<double, double> Point;
class Solution {
    int n;
public:
    double getMinDistSum(vector<vector<int> >& positions) {
        Point d, p;
        n = positions.size();
        double min_x = 101, min_y = 101, max_x = -1, max_y = -1;
        for (int i = 0; i < n; i++) {
            min_x = min(min_x, (double)positions[i][0]);
            min_y = min(min_y, (double)positions[i][1]);
            max_x = max(max_x, (double)positions[i][0]);
            max_y = max(max_y, (double) positions[i][1]);
        }
        p = make_pair((min_x + max_x) / 2, (min_y + max_y) / 2);
        double l_m;
        int i = 1;
        double i_step = 0.1;
x        double f_old = f_dis(positions, p);
        double f_new;
        Point p_new;
        Point move;
        double improve = 10000;
        double time = 1;
        do {
            d = diff(positions, p);
            move = d;
            move.first = -move.first * step;
            move.second = -move.second * step;
            l_m = len_d(move);
            p_new = p;
            p_new.first +=  move.first;
            p_new.second += move.second;
            f_new = f_dis(positions, p_new);
            improve = f_old - f_new;
            if (f_new < f_old) {
                p = p_new;
                f_old = f_new;
                time = 1;
            } else {
                time ++;
                step = i_step / (0.5 * time * time);
                
            }
            if (time > 1e3) {
                break;
            }
            
        } while (true);
        return f_old;
    }
};
int main() {
    Solution s;
    vector<vector<int> > positions {{0,1},{3,2},{4,5},{7,6},{8,9},{11,1},{2,12}};
    double res = s.getMinDistSum(positions);
    res = res + 0;
}