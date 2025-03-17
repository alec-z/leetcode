#include <utility>
#include <vector>
using namespace std;
const unsigned mod_p = 1e9 + 7;
const unsigned sqrt_max_num = 100;

const unsigned r_max_num = 14;
const unsigned max_num = 10000;
class Solution {

public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        int len = queries.size();

        vector<int> primes;
        vector<int> res(len, 0);
        vector<bool> is_prime(sqrt_max_num + 1, true);
        for (int i = 2; i <= sqrt_max_num; i++) {
            if (is_prime[i])
                for (int j = i * i; j <= sqrt_max_num; j+= i) is_prime[j] = false;
        }

        for (int i = 2; i <= sqrt_max_num; i++)
            if (is_prime[i]) {
                primes.push_back(i);
            }
        
        vector<vector<int>> comb(r_max_num + max_num + 1, vector<int> (r_max_num + 1, 0));
        comb[1][0] = 1, comb[1][1] = 1;
        for (int i = 2; i <= r_max_num + max_num ; i++) {
            comb[i][0] = 1;
            for (int r = 1; r <= r_max_num & r <= i; r++) {
                comb[i][r] = (comb[i - 1][r] + comb[i - 1][r - 1]) % mod_p;
            }
        }
        for (int i = 0; i < len; i++) {
            int num = queries[i][1];
            int buckets = queries[i][0];
            unsigned long long  all = 1;
            for (int p = 0; p < primes.size() && num >= 1; p++) {
                unsigned prime = primes[p];
                unsigned prime_pow = 0;
                while (num % prime ==0) {
                    prime_pow++;
                    num = num / prime;
                }
                if (prime_pow > 0) {
                    all *= comb[buckets + prime_pow - 1][prime_pow];
                    all %= mod_p;
                }
            }
            if (num > 100) {
                all *= buckets;
                all %= mod_p;
            }
            res[i] = all;
        }
        return move(res);
    }
};