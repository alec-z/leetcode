#include <string>
#include <set>
#include <iostream>
using namespace std;
class Solution {
public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        vector<vector<size_t>> hash(2, vector<size_t>(n,0));

        set<size_t> size_set;
        int res = 0;
        for (int size = 1; size <= n / 2; size++) {
            size_set.clear();
            for (int i = 0; i  < n + 1 - 1 * size; i++) {
                hash[size & 1][i] = hash[(size-1) & 1][i] * 31 + text[i + size - 1];
            }
            for (int i = 0; i < n + 1 - 2 * size; i++) {
                if (hash[size & 1][i] == hash[size & 1][i + size]) {
                    if (size_set.find(hash[size & 1][i]) == size_set.end())
                        res++;
                        size_set.insert(hash[size & 1][i]);
                    }
                    i += size - 1;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.distinctEchoSubstrings("leetcodeleetcode");
}