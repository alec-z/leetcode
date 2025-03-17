#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
typedef pair<double, double> Point;
const double epsilon =  numeric_limits<double>::epsilon();
class Solution {
    int n;
public:
    pair<double, double> diff(vector<vector<int> >& positions, Point p) {
        double dx = 0, dy = 0;
        double all_first = 0;
        for (int i = 0; i < n; i++) {
            double s_sum = ((double)positions[i][0] - p.first) * ((double)positions[i][0] - p.first) + ((double)positions[i][1] - p.second) * ((double)positions[i][1] -  p.second);
            if (abs(s_sum) < epsilon) {
                continue;
            }
            double first =  1 / sqrt(s_sum);
            dx += first * (positions[i][0] - p.first);
            dy += first * (positions[i][1] - p.second);
            all_first += first;
        }
        if (abs(all_first) < epsilon) {
            return make_pair(0, 0);
        }
        return make_pair(dx / all_first, dy / all_first);
    }

    double f_dis(vector<vector<int> >& positions, Point p) {
        double res = 0 ;
        for (int i = 0; i < n; i++) {
            res += sqrt((positions[i][0] - p.first) * (positions[i][0] - p.first) + (positions[i][1] - p.second) * (positions[i][1] - p.second));
        }
        return res;
    }


    
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
        int i = 1;
        Point move;
        do {
            move = diff(positions, p);
            i++;
            p.first += move.first;
            p.second += move.second;
        } while (abs(move.first) > 1e-6 || abs(move.second) > 1e-6);
        return f_dis(positions,p);
    }
};
int main() {
    Solution s;
    vector<vector<int> > positions {{0,1},{3,2},{4,5},{7,6},{8,9},{11,1},{2,12}};
    double res = s.getMinDistSum(positions);
    res = res + 0;
}