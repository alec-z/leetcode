#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int len = machines.size();
        int sum = 0;
        for (int i = 0; i < len; i++)
            sum += machines[i];
        if (sum % len  != 0) return -1;
        int avg = sum / len;
        int moves = 0;
        int first_unavg_pos = 0;
        while (first_unavg_pos < len) {
            first_unavg_pos = adjust_1_from(first_unavg_pos, machines, avg);
            if (first_unavg_pos < len) {
                moves++;
            }
        }
        return moves;
    }
private:
    int adjust_1_from(int i,  vector<int>& machines, int avg) {
        if (i >= machines.size()) return i;
        if (machines[i] < avg) {
            int j = i + 1;
            for (; j < machines.size() && machines[j] <= avg; j++) {}
            if (j == machines.size()) return j;
            else {
                machines[i]++;
                machines[j]--;
                adjust_1_from(j + 1, machines, avg);
                if (machines[i] == avg) {
                    return i + 1;
                } else {
                    return i;
                }
            }
        } else if (machines[i] > avg) {
            int j = i + 1;
            for (; j < machines.size() && machines[j] >= avg; j++) {}
            if (j == machines.size()) return j;
            else {
                machines[i]--;
                machines[j]++;
                adjust_1_from(j + 1, machines, avg);
                if (machines[i] == avg) {
                    return i + 1;
                } else {
                    return i;
                }
            }
        } else {
            return adjust_1_from(i + 1, machines, avg);
        }
    }
};

int main() {
    Solution s;
    vector<int> machines {0,0,10,0,0,0,10,0,0,0};
    cout << s.findMinMoves(machines) << endl;

}