#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
    int n;
    int min_steps;
    vector<int> rows;
    vector<int> label2pos;

    int should_pos(int label) {
        int mate = label / 2 * 2 + !(label % 2);
        int p_mate = label2pos[mate];
        return (p_mate % 2 == 1) ? p_mate - 1 : p_mate + 1;
    }
    void swap_with_m(int i, int j) {
        swap(rows[i], rows[j]);
        label2pos[rows[i]] = i;
        label2pos[rows[j]] = j;
    }
public:
    int minSwapsCouples(vector<int>& row) {
        this->rows = row;
        label2pos.resize(row.size(),0);
        for (int i = 0; i < row.size(); i++) {
            label2pos[row[i]] = i;
        }
        int res = 0;
        for (int i = 0; i < rows.size(); i++) {
            int j = i;
            int should_j;
            while ((should_j = should_pos(rows[j])) != j) {
                swap_with_m(should_j, j);
                res++;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> row {0,2,1,3};
    cout <<s.minSwapsCouples(row);
}