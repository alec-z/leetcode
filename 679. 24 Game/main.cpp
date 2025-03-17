#include <vector>
using namespace std;

class Solution {
    bool try_f(vector<double> &cards) {
        int n = cards.size();
        if (n == 1) {
            if (abs(cards[0] - 24) < 1e-8)
                return true;
            else return false;
        }
        vector<double> new_cards(n - 1);
        for (int i = 0; i < n - 1; i++) new_cards[i] = cards[i + 1];
        bool res = false;
        for (int i = 0; i < n ; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                for (int k = 0, k2 = 1; k < n; k++) {
                    if (k != i && k != j)
                        new_cards[k2++] = cards[k];
                } 
                new_cards[0] = cards[i] + cards[j];
                res = try_f(new_cards);
                if (res) return res;
                new_cards[0] = cards[i] - cards[j];
                res = try_f(new_cards);
                if (res) return res; 
                new_cards[0] = cards[i] * cards[j];
                res = try_f(new_cards);
                if (res) return res;
                new_cards[0] = cards[i] / cards[j];
                res = try_f(new_cards);
                if (res) return res;
            }
        }
        return res;
    }
public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> d_cards(cards.size());
        for (int i = 0; i < cards.size(); i++) 
            d_cards[i] = cards[i];
        return try_f(d_cards);
    }
};

int main() {
    Solution s;
    return 0;
}