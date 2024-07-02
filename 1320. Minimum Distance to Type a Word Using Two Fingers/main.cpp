#include <string>
#include <map>

using namespace std;
class Solution {
    map<tuple<int,int,int>, int> f_map;
    int try_f(int last_p, int last_f1_p, int last_f2_p) {
        auto t = make_tuple(last_p, last_f1_p, last_f2_p);
        auto p = f_map.find(t);
        if (p != f_map.end()) {
            return p->second;
        }
        if (last_p == 0) {
            f_map[t] = 0;
            return 0;
        }
        int min_cost = 10000000;
        #f1
        if (last_p == last_f1_p) {
            if (last_p - 1 == last_f2_p) {
                for (int f1_p = )
            }
        }
    } 
public:
    int minimumDistance(string word) {
        
    }
};