#include <string>
using namespace std;
class Solution {
    string num;
    int size;
public:
    string minInteger(string num, int k) {
        this->num = num;
        this->size = num.size();
        try_f(0, k);
        return this->num;
    }
    void try_f(int be, int k) {
        if (be == size) return;
        if (k == 0) return;
        int low_c = num[be];
        int low_p = be;
        for (int i = be; i <= be + k && i < size; i++) {
            if (num[i] < low_c) {
                low_c = num[i];
                low_p = i;
            }
        }
        int move = low_p - be;
        for (int i = low_p; i > be; i--) {
            num[i] = num[i - 1];
        }
        num[be] = low_c;
        try_f(be + 1, k - move);
    }
};