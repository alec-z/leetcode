#include <functional>
#include <vector>
#include <functional>
using namespace std;
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int len = jobs.size();
        sort(jobs.begin(), jobs.end(), greater<int>());
        vector<int> bucket(k, 0);
        int min_time = 1e9;
        function<void(int)> dfs = [&](int p) -> void {
            if (p == len) {
                min_time = min(min_time, *max_element(bucket.begin(), bucket.end()));
                return;
            }
            int seen[12];
            int sl = 0;

            int empty_bucket = 0;
            for (int j = 0; j < sl; j++) {
                if (bucket[j] == 0) {
                    empty_bucket++;
                }
            }

            if (((len - p) < empty_bucket) && p > k - empty_bucket) return;


            for (int i = 0; i < k; i++) {
                if (bucket[i] + jobs[p] > min_time) continue;
                bool found = false;
                for (int j = 0; j < sl; j++) {
                    if (seen[j] == bucket[i]) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    continue;
                }
                

                seen[sl++] = bucket[i];
                bucket[i] += jobs[p];
                dfs(p + 1);
                bucket[i] -= jobs[p];
            }
        };

        dfs(0);
        return min_time;
    }
};