#include <vector>
#include <map>
#include <tuple>
using namespace std;


class Solution {
    map<tuple<int, int, int>, int> func;
    int row_cherries(vector<int>& row, int last_out_x, int last_in_x, int out_x, int in_x) {
        int total = 0;
        for (int i = last_out_x; i <= out_x; i++) {
            if (row[i] == -1){
                return -1;
            }
            if (row[i] == 1) {
                total++;
            } 
        }

        for (int i = last_in_x; i <= in_x; i++) {
            if (row[i] == -1){
                return -1;
            }
            if (row[i] == 1 && !(i >= last_out_x && i <= out_x)) {
                total++;
            }
        }
        return total;
    }
    int try_cherry_pickup(vector<vector<int>>& grid, int row_y, int out_x, int in_x) {
        tuple<int, int, int> t = make_tuple(row_y, out_x, in_x);
        auto p = func.find(t);
        if (p != func.end()) {
            return p->second;
        }
        vector<int> &row = grid[row_y];
        if (row_y == 0) {
            int res = row_cherries(row, 0, 0, out_x, in_x);
            func[t] = res;
            return res;
        }
        if (row[out_x] == -1 || row[in_x] == -1) {
            func[t] = -1;
            return -1;
        }
        int max_pickup = -1;
        for (int last_out_x = out_x; last_out_x >= 0 && row[last_out_x] != -1; last_out_x--) {
            for (int last_in_x = in_x; last_in_x >= 0 && row[last_in_x] != -1; last_in_x--) {
                int last_row_pickup = try_cherry_pickup(grid, row_y - 1, last_out_x, last_in_x);
                if (last_row_pickup != -1) {
                    int single_row_pickup = row_cherries(grid[row_y], last_out_x, last_in_x, out_x, in_x);
                    if (single_row_pickup != -1 && (last_row_pickup + single_row_pickup) > max_pickup) {
                        max_pickup = last_row_pickup + single_row_pickup;
                    }
                }
            }
        }
        func[t] = max_pickup;
        return max_pickup;
    }
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int res = try_cherry_pickup(grid, grid.size() - 1, grid[0].size() - 1, grid[0].size() - 1);
        return res == -1 ? 0 : res;
    }
};