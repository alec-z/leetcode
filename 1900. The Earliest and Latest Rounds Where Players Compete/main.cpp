#include <tuple>
#include <utility>
#include <vector>
#include <functional>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        vector<int> a_res(2);
        vector<int> row(n);
        
        map<tuple<int,int,int>, pair<int, int>> dp_m;


        function<pair<int, int> (int, int, int)> try_f = [&](int n, int first, int second) -> pair<int,int> {
            tuple<int,int,int> para = make_tuple(n, first, second);
            auto p = dp_m.find(para);
            if (p !=  dp_m.end()) {
                return p->second;
            }
            int rs = n;
            int mask_len = n / 2;
            size_t mask_top = (size_t)(ceil(pow(2, mask_len)));
            int row_len = mask_len + n % 2;
            pair<int, int> res = make_pair(100000, 0);
            for (size_t mask = 0; mask < mask_top; mask++) {
                size_t tm_mask = mask;
                bool consisted = true;
                for (int i = 0; i < mask_len; i++) {
                    const auto p1 = i + 1;
                    const auto p2 = n - i;
                    const auto winner = (tm_mask & 1u) == 0 ? p1 : p2;
                    const auto loser = (tm_mask & 1u) == 0 ? p2 : p1;
                    if ((winner == first && loser == second) || (winner == second && loser == first)) {
                        return dp_m[para] = make_pair(1, 1);
                    } else if ((winner != first && winner != second) && (loser == first || loser == second)) {
                        consisted = false;
                        break;
                    } else {
                        row[i] = winner;
                    }
                    tm_mask = tm_mask >> 1;
                }
                if (!consisted) {
                    continue;
                }
                if (row_len > mask_len) row[row_len - 1] = row_len;
                sort(row.begin(), row.begin() + row_len);
                int n_first, n_second;
                for (int i = 0; i < row_len; i++) {
                    if (row[i] == first) n_first = i + 1;
                    else if (row[i] == second) n_second = i+1;
                }
                auto sub_res = try_f(row_len, n_first, n_second);
                res.first = min(res.first, sub_res.first);
                res.second = max(res.second, sub_res.second);
            }
            res.first += 1;
            res.second += 1;
            dp_m[para] = res;
            return res;
        };
        auto p_res = try_f(n, firstPlayer, secondPlayer);
        a_res[0] = p_res.first;
        a_res[1] = p_res.second;
        return a_res;
    }
};
int main() {
    Solution s;
    auto p = s.earliestAndLatest(11, 2, 4);
    int i = 0;
}