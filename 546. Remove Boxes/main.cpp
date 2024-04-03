#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
struct Node {
    int key;
    int len;
};

struct NodeScore {
    int key;
    int score;
};

class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        vector<Node> new_boxes;
        int cur = boxes[0];
        int cur_len = 1;
        for (int i = 1; i < boxes.size(); i++) {
            if (boxes[i] == cur) cur_len++;
            else {
                new_boxes.push_back({cur, cur_len});
                cur = boxes[i];
                cur_len = 1;
            }
        }
        new_boxes.push_back({cur, cur_len});
        return try_max_score(new_boxes);
    }
private:
    int try_max_score(vector<Node> & new_boxes) {
        if (new_boxes.size() == 1) return new_boxes[0].len * new_boxes[0].len;
        vector<int> sums(101);
        for (int i = 0; i < new_boxes.size(); i++) {
            sums[new_boxes[i].key] += new_boxes[i].len;
        }
        int min_gap = 1000000;
        int max_len = 0;
        int pos = -1;

        for (int i = 0; i < new_boxes.size(); i++) {
            int cur_key = new_boxes[i].key;
            int gap = sums[cur_key] - new_boxes[i].len;
            if (gap < min_gap || (gap == min_gap && new_boxes[i].len > max_len)) {
                min_gap = gap;
                max_len = new_boxes[i].len;
                pos = i;
            }
        }
        new_boxes.erase(new_boxes.begin() + pos);
        if (pos < new_boxes.size() && pos > 0) {
            if (new_boxes[pos - 1].key == new_boxes[pos].key) {
                new_boxes[pos - 1].len += new_boxes[pos].len;
                new_boxes.erase(new_boxes.begin() + pos);
            }
        }

        return max_len * max_len + try_max_score(new_boxes);
    }
};

int main() {
    Solution s;
    vector<int> boxes {1,3,2,2,2,3,4,3,1};
    cout << s.removeBoxes(boxes) << endl;

}