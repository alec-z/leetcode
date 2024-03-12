#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int len = profits.size();
        vector<int> pre(len, w), cur(len, 0);

        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < len; j++) {
                if (j == 0) {
                    if (w >= capital[0]) 
                        cur[0] = w + profits[0];
                    else 
                        cur[0] = w; 
                    continue;
                }
                cur[j] = cur[j - 1];
                if (capital[j] <= pre[j - 1] && (pre[j - 1] + profits[j]) > cur[j]) {
                    cur[j] = pre[j - 1] + profits[j];
                }
            }
            pre.swap(cur);
        }
        return pre[len - 1];
    }
};

int main() {
    Solution s;
    int k = 2, w = 0;
    vector<int> profits = {1,2,3};
    vector<int> capital = {0,1,1};
    cout << s.findMaximizedCapital(k, w, profits, capital) << endl;
}