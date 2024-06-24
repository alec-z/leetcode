#include <limits>
#include <map>
#include <vector>
#include <limits>
#include <iostream>
using namespace std;

class Solution {
    map<pair<int, int>, int> func;
    vector<int> stones;
    vector<int> sums;
    bool check_interval(int be, int en, int k) {
        if (be >= en)
            return false;
        return (en - be - 1) % (k - 1) == 0;
    }
    int try_f(int be, int en, int k) {
        auto p = func.find(make_pair(be, en));
        if (p != func.end())
            return p->second;
        if (!check_interval(be, en, k))
            return -1;
        if (en - be == 1) {
            func[make_pair(be, en)] = stones[be];
            return stones[be];
        }
        vector<int> split(k, -1);
        split[0] = be;
        int level = 0;
        int min_f = numeric_limits<int>::max();
        while (level >= 0) {
            split[level]++;
            if (split[level] > en) {
                level--;
            } else {
                int pre = be;
                if (level > 0) {pre = split[level - 1];}
                if (!check_interval(pre, split[level], k)) {
                    continue;
                }
                if (level == k - 2) {
                    if (!check_interval(split[level], en, k)) {
                        continue;
                    }
                    int sum = 0;
                    int start = be;
                    for (int j = 0; j < k - 1; j++) {
                        sum += try_f(start, split[j], k);
                        if (split[j] - start > 1) {
                            sum += sums[split[j]] - sums[start];
                        }
                        start = split[j];
                    }
                    sum += try_f(start, en, k);
                    if (en - start > 1) {
                        sum += sums[en] - sums[start];
                    }
                    if (sum < min_f) {
                        min_f = sum;
                    }
                } else {
                    level++;
                    split[level] = split[level - 1];
                }
            }
        }
        func[make_pair(be, en)] = min_f;
        return min_f;
    }

  public:
    int mergeStones(vector<int> &stones, int k) {
        if (stones.size() == 1) return 0;
        this->stones = stones;
        sums.resize(stones.size() + 1, 0);
        for (int i = 1; i <= stones.size(); i++) {
            sums[i] = sums[i - 1] + stones[i - 1];
        }
        int len = stones.size();
        return try_f(0, len, k);
    }
};

int main() {
    vector<int> nums = {3,2,4,1};
    Solution s;
    cout << s.mergeStones(nums, 2);
}