#include <string>
#include <unordered_map>
#include <map>
using namespace std;
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;              
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};

class Solution {
    unordered_map<pair<int,int>, int, hash_pair> f_map;
    string str;
    int try_f(int be, int en) {
        auto p = f_map.find(make_pair(be, en));
        if (p != f_map.end()) {
            return p->second;
        }
        int res = 0;
        int min_res = 10000000;
        if (be >= en) {
            res = 0;
            f_map[make_pair(be, en)] = res;
            return 0;
        }
        if (str[be] == str[en]) {
            res = try_f(be + 1, en -1);
            if (res < min_res) min_res = res;
        }

        res = 1 + try_f(be + 1, en);
        if (res < min_res) min_res = res;

        res = 1 + try_f(be, en - 1);
        if (res < min_res) min_res = res;

        f_map[make_pair(be, en)] = min_res;
        return min_res;
    }
public:
    Solution(): f_map() {

    }
    int minInsertions(string s) {
        this->str = s;
        return try_f(0, str.size() - 1);
    }
};