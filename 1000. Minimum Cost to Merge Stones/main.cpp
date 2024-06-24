#include <vector>
#include <limits>
using namespace std;

class Solution {
    int k;
    int total = 0;
    int merge(vector<int>& stone, int len, int i) {
        if (i + k > len) {
            return -1;
        }
        for (int j = i + 1; j < i + k; j++) {
            stone[i] += stone[j];
        }
        for (int j= i + 1; j < len - k + 1; j++) {
            stone[j] = stone[j + k - 1];
        }
        total += stone[i];
        return len - k + 1;
    }
    int find_k_min(vector<int>& stone, int len) {
        if (len < k) return -1;
        int sum = 0;
        for (int j = 0; j < k; j++) {
            sum += stone[j];
        }
        int min = sum;
        int pos = 0;
        for (int j = 1; j <= len - k; j++) {
            sum = sum - stone[j - 1] + stone[j + k - 1];
            if (sum < min) {
                min = sum;
                pos = j;
            }
        }
        return pos;

    }
public:
    int mergeStones(vector<int>& stones, int k) {
        int len = stones.size();
        this->k = k;
        while (len > 1) {
            int p = find_k_min(stones, len);
            if (p == -1) {
                return -1;
            }
            len = merge(stones, len, p);
            if (len == -1) {
                return -1;
            }
        }
        return total;
    }
};

int main() {
    vector<int> nums = {3,5,1,2,6};
    Solution s;
    s.mergeStones(nums,3);
}