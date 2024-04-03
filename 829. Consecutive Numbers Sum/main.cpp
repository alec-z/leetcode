#include <iostream>
#include <math.h>

using namespace std;
class Solution {
public:
    int consecutiveNumbersSum(int n) {
        long product = (long)n * 2;
        int upper = floor(sqrt<long>(product)); 
        int res = 0;
        for (int i = 2; i <= upper; i++) {
            if (product % i == 0) {
                int f = (product / i) - i + 1;
                if (f > 1 && f % 2 == 0) {
                    res++;
                } 
            }
        }
        return res;
    }
};