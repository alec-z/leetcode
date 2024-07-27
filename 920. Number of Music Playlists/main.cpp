#include <map>

using namespace std;
const long mod_p = 1e9 + 7;

class Solution {
    map<pair<int, int>, long> f_map;
public:
    int numMusicPlaylists(int n, int goal, int k) {
        auto x = make_pair(goal, n);
        auto p = f_map.find(x);
        if (p != f_map.end()) {
            return p->second; 
        }
        if (n == goal) {
            long res = 1;
            for (int i = 1; i <= n; i++) {
                res *= i;
                res %= mod_p;
            }
            f_map[x]= res;
            return res;
        }
        if (n > goal || n <= k || n <= 0 || goal <=0) {
            f_map[x]= 0;
            return 0;
        }
        if (n == 1 && n >=k) {
            f_map[x] = 1;
            return 1;
        }
        long part1 = (long)numMusicPlaylists(n - 1, goal - 1, k) * n % mod_p;
        long part2 =  0;
        if (goal - 1 > k)
            part2 = (long)numMusicPlaylists(n, goal - 1, k) * (n - k) % mod_p;
        else
            part2 = (long)numMusicPlaylists(n, goal - 1, k) * n % mod_p;
        long res = (part1 + part2) % mod_p;
        f_map[x] = res;
        return res;
    }
};

int main() {
    Solution s;
    s.numMusicPlaylists(2, 3, 0);
}