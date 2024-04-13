#include <iostream>

struct FuncValue {
    size_t left_LL_A_0;
    size_t left_LL_A_1;
    size_t left_LO_A_0;
    size_t left_LO_A_1;
    size_t left_O_A_0;
    size_t left_O_A_1;
};
const size_t modP = 1000000000 + 7;
class Solution {
    int sum(FuncValue & v) {
        size_t all = v.left_LL_A_0 + v.left_LL_A_1 + v.left_LO_A_0 + v.left_LO_A_1 + v.left_O_A_0 + v.left_O_A_1;
        return all % modP;
    }
public:
    int checkRecord(int n) {
        if (n == 0) return 0;
        if (n == 1) return 3;
        FuncValue pre{1,0,1,1,2,3}, cur;
        for (int i = 3; i <= n; i++) {
            cur.left_LL_A_0 = pre.left_LO_A_0 ;
            cur.left_LL_A_1 = pre.left_LO_A_1;
            cur.left_LO_A_0 = pre.left_O_A_0;
            cur.left_LO_A_1 = pre.left_O_A_1;
            cur.left_O_A_0 = (pre.left_LL_A_0 + pre.left_LO_A_0 + pre.left_O_A_0) % modP;
            cur.left_O_A_1 = ((pre.left_LL_A_0 + pre.left_LO_A_0 + pre.left_O_A_0) +  
            (pre.left_LL_A_1 + pre.left_LO_A_1 + pre.left_O_A_1)) % modP;
            pre = cur;
        }
        return sum(pre);
    }
};