#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Job {
    int s;
    int e;
    int p;
};
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<Job> jobs(n);
        for (int i = 0; i < n; i++) {
            jobs[i].s = startTime[i];
            jobs[i].e = endTime[i];
            jobs[i].p = profit[i];
        }
        sort(jobs.begin(), jobs.end(), [](const Job & a, const Job &b) {
            return a.e < b.e || (a.e == b.e && a.s > b.s); 
        });
        map<int, int> f;
        f[0] = 0;
        int max = 0;
        for (int i = 0; i < n; i++) {
            auto & cur_j = jobs[i];
            auto p = f.upper_bound(cur_j.s);
            p--;
            int cur_j_f = p->second + cur_j.p;
            if (cur_j_f > max) {
                max = cur_j_f;
                f[cur_j.e] = max;
            }
        }
        return max;
    }
};

