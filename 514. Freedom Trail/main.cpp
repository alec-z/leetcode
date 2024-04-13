#include <string>
#include <map>
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    class Resolution {
        public:
            const string & ring;
            const string & key;
            int ring_len;
            map<pair<int, int>, int> func;
            map<char, vector<short>> char_to_pos;
            Resolution(const string & ring, const string & key) : ring(ring), key(key) {
                for (int i = 0; i < ring.size(); i++) {
                    char_to_pos[ring[i]].push_back(i);   
                }
                ring_len = ring.size();
            }
            int min_step(int anti_clock_wise, int remain) {
                auto pair = make_pair(anti_clock_wise, remain);
                if (func.find(pair) != func.end()) {
                    return func[pair];
                }
                int min_move = numeric_limits<int>::max();
                if (remain == 0) {
                    func[pair] = 0;
                    return 0;
                }
                char cur_char = key[key.size() - remain];
                for (auto pos: char_to_pos[cur_char]) {
                    int anti_clock_move = ((pos - anti_clock_wise) + ring_len) % ring_len;
                    int clock_move = ring_len - anti_clock_move;
                    int all_move;
                    if (anti_clock_move <= clock_move) {
                        all_move = anti_clock_move + min_step((anti_clock_wise + anti_clock_move) % ring_len, remain - 1) + 1;
                    } else {
                        all_move = clock_move + min_step((anti_clock_wise - clock_move + ring_len) % ring_len, remain - 1) + 1;
                    }
                    if (all_move < min_move) {
                        min_move = all_move;
                    }
                }
                
                func[pair] = min_move;
                return min_move;
            } 
    };
    int findRotateSteps(string ring, string key) {
        Resolution re_sol(ring, key);
        return re_sol.min_step(0, key.size());
    }
};

int main() {
    Solution s;
    cout << s.findRotateSteps("godding", "godding") << endl;
}