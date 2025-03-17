#include <string>
#include <vector>
#include <limits>

using namespace std;
const int MIN_INT = numeric_limits<int>::min();
class Solution {
    int n;
    vector<int> win_score_from_func;
public:
    string stoneGameIII(vector<int>& stoneValue) {
        n = stoneValue.size();
        win_score_from_func.resize(n, MIN_INT);
        int win = win_score_from(stoneValue, 0);
       
        if (win > 0) return "Alice";
        else if (win == 0) return "Tie";
        else return "Bob";
    }
    int win_score_from(vector<int>& stones, int be) {
        if (be >= n) {
            return 0;
        }
        if (win_score_from_func[be] > MIN_INT) {
            return win_score_from_func[be];
        }
        
        int best = MIN_INT;
        int sum = 0;
        for (int i = 0; i < 3 && be + i < n ; i++) {
            sum += stones[be + i];
            best = max(best, sum - win_score_from(stones,  be + i + 1));
        }
        win_score_from_func[be] = best;
        return best;
    }
};