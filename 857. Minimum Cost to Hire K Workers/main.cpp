#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct WorkerQ {
    int quality;
    int wage;
    double w_per_q;
};
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<WorkerQ> w_list(n);
        for (int i = 0; i < n; i++) {
            w_list[i].quality = quality[i];
            w_list[i].wage = wage[i];
            w_list[i].w_per_q = wage[i] / (double)(quality[i]);
        }
        sort(w_list.begin(), w_list.end(), [](const WorkerQ & a, const WorkerQ &b) {
            return a.quality < b.quality;
        });

        auto priority_f =  [](const WorkerQ & a, const WorkerQ &b) {
            return a.w_per_q < b.w_per_q || ( a.w_per_q == b.w_per_q && a.quality < b.quality);
        };

        priority_queue<WorkerQ, vector<WorkerQ>, decltype(priority_f)> p_q(priority_f);
        int sum_q = 0;
        double total_wage = 0;
        double min_total_wage = 1e12;
        for (int i = 0; i < k; i ++) {
            p_q.push(w_list[i]);
            sum_q += w_list[i].quality;
        }
        auto current_worker = p_q.top();
        total_wage = current_worker.w_per_q * sum_q;
        min_total_wage = total_wage;
        for (int i = k; i < n; i++) {
            if (w_list[i].w_per_q < current_worker.w_per_q) {
                sum_q -= current_worker.quality;
                sum_q += w_list[i].quality;
                p_q.pop();
                p_q.push(w_list[i]);
                current_worker = p_q.top();
                total_wage = current_worker.w_per_q * sum_q;
                if (total_wage < min_total_wage) {
                    min_total_wage = total_wage;
                }
            }
        }
        return min_total_wage;
    }
};