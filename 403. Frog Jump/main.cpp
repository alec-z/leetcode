#include <vector>
#include <iostream>
#include <set>
#include <map>

using namespace std;

class Solution {
public:
    bool canCross(vector<int>& stones) {
        if (stones[1] != 1) return false;
        int len = stones.size();
        if (len == 2) return true;
        int target = stones[len - 1];

        map<int, set<int>> stone_jumps;
        for (int i = 1; i < stones.size(); i++) {
            stone_jumps[stones[i]] = {};
        }
        stone_jumps[1].insert(1);


        for (int i = 1; i < len; i++) {
            int stone = stones[i];
            auto p = stone_jumps.find(stone);
            const auto & set = (*p).second;
            for (int k: set) {
                if (stone_jumps.find(stone + k) != stone_jumps.end()) {
                    stone_jumps[stone + k].insert(k);
                    if (stone + k == target) return true;
                }
                if (stone_jumps.find(stone + k + 1) != stone_jumps.end()) {
                    stone_jumps[stone + k + 1].insert(k + 1);
                    if (stone + k + 1== target) return true;
                }
                if (k > 1 && stone_jumps.find(stone + k - 1) != stone_jumps.end()) {
                    stone_jumps[stone + k - 1].insert(k - 1);
                    if (stone + k - 1== target) return true;
                }
            }
            stone_jumps.erase(p);
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> stones {0,1,3,5,6,8,12,17};
    cout << s.canCross(stones) << endl;
}