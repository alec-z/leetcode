#include <string>
#include <tuple>
#include <map>
using namespace std;
class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        
    }
    class SubSol {
        string &s;
        int k;
        map<tuple<int,int, char, int>, int> h_m;
        public:
            SubSol(string & s, int k): s(s), k(k) {
            }
            int try_f(int len,int k, char last_c, int repeat) {
                if (s[len - 1] == last_c) {
                    if (repeat == 1) {
                        return try_f(len - 1, k, xxx, xx );
                        
                    } else if (repeat > 1) {
                        if (repeat == 2 || repeat == 10 || repeat == 100) {
                            return 1 + try_f(len - 1, k, last_c, repeat - 1)
                        } else {
                            return try_f(len - 1, k, last_c, repeat - 1);
                        }
                    }
                } else {
                    return 1 + try(len - 1, k - 1, last_c, repeat);
                }
            }
    };
};