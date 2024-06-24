#include <algorithm>
using namespace std;
class Solution {
    int try_f(int n, int m, int y, int x) {
        if (n > m) { 
            swap(n, m);
            swap(y, x); 
        }
        if (n == m && x == 0 && y == 0) {
            return 1;
        }
        int min_res = 100000000;

        if (x == 0 && y == 0) {
            for (int l = n; l > 0; l--) {
                if (l == n) {
                    int tmp =  1 + try_f(n, m - n, 0, 0);
                    if (tmp < min_res) min_res = tmp;
                }
                else {
                    int tmp = 1 + try_f(n, m, l, l);
                    if (tmp < min_res) min_res = tmp;
                }
            }
        } else {
            int h = n - y;
            int w = x;
             int tmp;
            if (h < w) {
                tmp =  1 + try_f(n, m-h, y, x - h);
            } else if (h == w) {
                tmp =  1 + try_f(n, m - h, 0, 0);
            } else {
                tmp = 1 + try_f(n, m - x, h, h - w);
            }
            if (tmp < min_res) min_res = tmp;
        }
        return min_res;


    }
public:
    int tilingRectangle(int n, int m) {
        return try_f(n, m, 0, 0);
    }
};