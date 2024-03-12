#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int len = profits.size();

        vector<pair<int, int>> projects(len);
        for (int i = 0; i < len; i++) {
            projects[i].first = capital[i];
            projects[i].second = profits[i];
        }
        sort(projects.begin(), projects.end());
        priority_queue<int> qe;
        int pos = 0;
        int cur_w = w;
        while (k > 0) {
            for (;  pos < len && projects[pos].first <= cur_w; pos++) {
                qe.push(projects[pos].second);
            }
            if (qe.empty())
                break;
            else {
                cur_w += qe.top();
                qe.pop();
            }
            k--;
        }
        return cur_w;
    }
};

int main() {
    Solution s;
    int k = 2, w = 0;
    vector<int> profits = {1,2,3};
    vector<int> capital = {0,1,1};
    cout << s.findMaximizedCapital(k, w, profits, capital) << endl;
}