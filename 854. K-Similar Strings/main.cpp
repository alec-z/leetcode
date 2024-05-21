
#include <algorithm>
#include <map>
#include <string>
#include <limits>
using namespace std;
class Solution {
public:
    int kSimilarity(string s1, string s2) {
        SubSol ss(s1, s2);
        return ss.try_f(s1);
    }
    class SubSol {
        map<string, int> func;
        string s1;
        string s2;
        int s2_len;
        public:
            SubSol(const string &s1, const string & s2): s1(s1), s2(s2) {
                s2_len = s2.size();
            }
            int try_f(string s) {
                int len = s.size();
                int start = s2_len - len;
                int res_min = numeric_limits<int>::max() - 10000;
                int res_temp = 0;
                if (s.size() == 1) 
                    return 0;
                auto p = func.find(s);
                if (p != func.end()) {
                    return p->second;
                }
                for (int i = 0; i < len; i++) {
                    if (s[i] == s2[start]) {
                        string s_new = s;
                        swap(s_new[0], s_new[i]);
                        if (i == 0) 
                            res_temp = try_f(s_new.substr(1, len -1));
                        else
                            res_temp = 1 + try_f(s_new.substr(1, len - 1));
                        if (res_temp < res_min) {
                            res_min = res_temp;
                        }
                    }
                }
                func[s] = res_min;
                return res_min;
            }
    };
};