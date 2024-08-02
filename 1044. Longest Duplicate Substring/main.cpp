#include <string>
#include <map>
using namespace std;
const long prim = 10737418;
class Solution {
    map<long, int> hashes;
    int res;
    int res_pos;

    void try_len(const string &s, int be, int en) {
        if (be > en) return;
        int mid = (be + en + 1) / 2;
        long pre = 0;
        hashes.clear();
        long power_31 = 1;
        for (int i = 0; i < mid; i++) {
            pre = pre * 31 + s[i] - 'a';
            pre %= prim;
            if (i > 0) 
                power_31 = power_31 * 31 % prim;
        }
        hashes[pre] = 0;
        int i = 1;
        for (i = 1; i + mid - 1 < s.size(); i++) {
            pre = ((pre - power_31 * (s[i - 1] - 'a') % prim + prim) * 31 + (s[i + mid -1] - 'a')) % prim;
            if (hashes.find(pre)!= hashes.end() && s.substr(hashes[pre], mid) == s.substr(i, mid)) {
                if (mid > res) {
                        res = mid;
                        res_pos = i;
                }
                try_len(s, mid + 1, en);
                break;
            } else {
                hashes[pre] = i;
            }
        }
        if (i + mid - 1 == s.size()) {
            try_len(s, be, mid - 1);
        }
    }

public:
    string longestDupSubstring(string s) {
        res = -1;
        try_len(s, 1, s.size() - 1);
        return  res == -1 ? "": s.substr(res_pos, res);
    }
};

int main() {
    Solution s;
    s.longestDupSubstring("banana");
}