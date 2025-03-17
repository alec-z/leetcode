#include <vector>
#include <algorithm>
using namespace std;
class Solution {
    int pivot_b;
    int pivot_a;
    bool is_great(int me, int bob, int alice) {
        return (me >= pivot_a && bob <= pivot_b && alice <= pivot_b) && (me > bob || me > alice);
    }
    bool is_enough(int me, int bob, int alice) {
        return me >= pivot_a && bob <= pivot_b && alice <= pivot_b;
    }
public:
    int maxSizeSlices(vector<int>& slices) {
        vector<int> copy_slices;
        copy_slices = slices;
        sort(copy_slices.begin(), copy_slices.end());
        int n = copy_slices.size();
        pivot_b = copy_slices[n / 3 * 2 - 1];
        pivot_a = copy_slices[ n / 3 * 2];
        int res = 0;
        
        while(n > 0) {
            int i = 0;
            for (i = 0; i < n; i++) {
                if (is_great(slices[i], slices[(i + 1) % n], slices[(i - 1 + n) %n])) {
                    break;
                } 
            }
            if (i == n) {
                for (i = 0; i < n; i++) {
                    if (is_enough(slices[i], slices[(i + 1) % n], slices[(i - 1 + n) %n ])) {
                        break;
                    } 
                }
            }
            int j = 0;
            res += slices[i];
            for (int k = 0; k < n - 3; k++) {
                while (j == i || j == (i + 1) % n || j == (i - 1 + n) % n) j++;
                slices[k] = slices[j];
                j++;
            }
            n -= 3;
        } 
        return res;
    }
};

int main() {
    Solution s;
    vector<int> input {1,2,3,4,5,6};
    s.maxSizeSlices(input);
}