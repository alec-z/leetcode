#include <vector>
#include <iostream>
using namespace std;
const int mod_p = 1e9 + 7;
class Solution {
    pair<int, int> intersect(long be0, long en0, long be1, long en1) {
        if (be0 <= be1) {
            return (en1 >= en0) ? make_pair(be1, en0) : make_pair(be1,en1);
        } else {
            return (en0 >= en1) ? make_pair(be0, en1) : make_pair(be0, en0);
        }
    }
    long area(const vector<int> &a) {
        return (long)(a[2] - a[0]) * (a[3] - a[1]) % mod_p;
    }
    const vector<int> overlap_rectangle(const vector<int> &a,
                                         const vector<int> &b) {
        vector<int> res{-1, -1, -1, -1};
        auto x_p = intersect(a[0], a[2], b[0], b[2]);
        auto y_p = intersect(a[1], a[3], b[1], b[3]);
        if (x_p.first >= x_p.second || y_p.first >= y_p.second) {
            return move(res);
        } else {
            res[0] = x_p.first;
            res[2] = x_p.second;
            res[1] = y_p.first;
            res[3] = y_p.second;
            return move(res);
        }
    }

  public:
    int rectangleArea(vector<vector<int>> &rectangles) {
        vector<vector<int>> cur_set = rectangles;
        vector<vector<int>> next_set;
        long sum = 0;
        long mark = 1;
        while (!cur_set.empty()) {
            next_set.clear();
            for (int i = 0; i < cur_set.size(); i++) {
                sum += (mod_p + mark * area(cur_set[i]));
                sum %= mod_p;
                for (int j = i + 1; j < cur_set.size(); j++) {
                    auto overlap = overlap_rectangle(cur_set[i], cur_set[j]);
                    if (overlap[0] != -1) {
                        next_set.push_back(overlap);
                    }
                }
            }
            cur_set = move(next_set);
            mark = mark * (-1);
        }
        return sum % mod_p;
    }
};

int main() {
    vector<vector<int>> rectangles  = {{0,0,2,2},{1,0,2,3},{1,0,3,1}};
    Solution s;
    cout << s.rectangleArea(rectangles);
}