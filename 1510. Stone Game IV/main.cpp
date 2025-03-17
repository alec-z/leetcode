#include <vector>
#include <cmath>
using namespace std;
class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<char> func(n + 1, 0);
        func[0] = 1;
        return try_f(func, n);

    }
    
    bool try_f(vector<char> & func, int n) {
        if (func[n] > 0) {
            return func[n] == 1 ? false : true;
        }

        
        int max = ceil(sqrt(n));
        for (int m = 1; m <= sqrt(n); m++) {
            if (m * m <= n) {
                int remain = n - m * m;
                if (!try_f(func, remain)) {
                    func[n] = 2;
                    return true; 
                }
            }
        }
        func[n] = 1;
        return false;
    }
};