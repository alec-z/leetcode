#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int pre = 0;
        int all = 0;    
        int n = target.size();
        for (int i = 0; i <  n; i++) {
            if (target[i] > pre) {
                all += target[i] - pre;
                pre = target[i];
            } else {
                pre = target[i];
            }
        }
        return all;
            
    }
};