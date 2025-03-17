#include <string>

using namespace std;

const unsigned long prim = 31;

class Solution {
public:
    string longestPrefix(string s) {
        unordered_map<unsigned long, int> prefix_hash;
        int n = s.size();
        unsigned long pre_hash = 0;
        unsigned long suf_hash = 0;
        unsigned long prim_order = 1;
        int max_len = 0;
        int i, j;
        for (int size = 1; size <= n - 1; size++) {
            i = size - 1;
            pre_hash = pre_hash * prim + s[i];

            j = n - size;
            suf_hash = prim_order * s[j]  + suf_hash;
            prim_order *= prim;
            if (pre_hash == suf_hash) {
                max_len = size;
            }
        }
        return s.substr(0, max_len);
    }
};
int main() {
    Solution s;
    string str = "level";
    s.longestPrefix(str);
}