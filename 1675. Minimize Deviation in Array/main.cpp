#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>> minHeap;
        for (auto n: nums) minHeap.push(n);
        while (minHeap.top() <= 1e9 && minHeap.top() % 2 == 1) {
            unsigned int new_v = minHeap.top() * 2;
            minHeap.pop();
            minHeap.push(new_v);
        }
        unsigned int min_v = minHeap.top();
        unsigned int res = numeric_limits<unsigned int>::max();
        priority_queue<unsigned int, vector<unsigned int>> maxHeap;
        while (!minHeap.empty()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        while (maxHeap.top() % 2 == 0) {
            res = min(res, maxHeap.top() - min_v);
            unsigned int new_v = maxHeap.top() / 2;
            if (new_v < min_v) min_v = new_v;
            maxHeap.pop();
            maxHeap.push(new_v);
            if (res <= 1) return res;
        }
        res = min(res, maxHeap.top() - min_v);
        return res;
    }
};

int main() {
    vector<int> nums = {1,2,3,4};
    Solution s;
    cout << s.minimumDeviation(nums) << endl;
}