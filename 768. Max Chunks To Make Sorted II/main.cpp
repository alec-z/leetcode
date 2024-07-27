#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        vector<int> sorted_arr = arr;
        sort(sorted_arr.begin(), sorted_arr.end());
        unordered_map<int, int> num2pos(arr.size());
        num2pos[sorted_arr[0]] = 0;
        for (int i = 1; i < sorted_arr.size(); i++) {
            if (sorted_arr[i] > sorted_arr[i-1]) {
                num2pos[sorted_arr[i]] = i;
            }
        }
        int max_pos = -1;
        int max_val = -1;
        int res = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] > max_val) {
                max_val = arr[i];
                max_pos = num2pos[max_val];
            } else if (arr[i] == max_val) {
                max_pos++;
            }
            if (i == max_pos) res++;
        }
        return res;

    }
};

int main() {
    Solution s;
    vector<int> arr = {5,4,3,2,1};
    s.maxChunksToSorted(arr);

}