#include <vector>
#include <map>
#include <iostream>
using namespace std;

const long long prime1 = 44326767;
const long long prime2 = 32034317;
typedef pair<long, long> FP;

class Solution {
    FP getFP(long num) {
        return make_pair(num % prime1, num % prime2);
    }
    FP getFP_range(int i, int j, const vector<FP> & forward, const vector<FP> & two_n) {
        long f = (forward[j - 1].first - forward[i].first * two_n[j - 1 - i].first % prime1 + prime1) % prime1;
        long s = (forward[j - 1].second - forward[i].second * two_n[j - 1 - i].second % prime2 + prime2) % prime2;
        return make_pair(f, s);
    }
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        
        int len = arr.size();
        vector<FP> two_n(len + 1);
        vector<FP> forward(len + 1);
        two_n[0] = make_pair(1, 1);
        forward[0] = make_pair(arr[0], arr[0]);
        
        map<FP, vector<int>> forward_m;
        forward_m[forward[0]].push_back(0);
        for (int i = 1; i < len; i++) {
            forward[i] = make_pair((forward[i - 1].first * 2 + arr[i]) % prime1, (forward[i - 1].second * 2 + arr[i]) % prime2);
            forward_m[forward[i]].push_back(i);
            two_n[i] = make_pair(two_n[i - 1].first * 2 % prime1, two_n[i - 1].second * 2 % prime2);
        }
        FP last = make_pair(0, 0);
        for (int j = len - 1; j >= 0; j--) {
            int two_n_s = len - 1 - j;
            last = make_pair((arr[j] * two_n[two_n_s].first + last.first) % prime1, (arr[j] * two_n[two_n_s].second + last.second) % prime2);
            for (auto i : forward_m[last]) {
                if (j > i + 1) {
                    if (getFP_range(i, j, forward, two_n) == last) {
                        return vector<int> {i, j};
                    }
                }
            }
        }
        return vector<int> {-1, -1};
    }
};

int main() {
    Solution s;
    vector<int> arr = {1,0,1,0,1};
    auto p = s.threeEqualParts(arr);
}