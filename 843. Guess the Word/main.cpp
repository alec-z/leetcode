#include <vector>
#include <string>
#include <set>
using namespace std;
class Solution {
    int match_num_f(string & a, string & b) {
        int res = 0;
        for (int i = 0; i < a.size(); i++) 
            if (a[i] == b[i]) res++;
        return res;
    }
public:
    void findSecretWord(vector<string>& words, Master& master) {
        int n = words.size();
        int l = words[0].size();
        vector<vector<int>> matches(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            matches[i][i] = l;
            for (int j = i + 1; j < n; j++) {
                int match = match_num_f(words[i], words[j]);
                matches[i][j] = match;
                matches[j][i] = match;
            }
        }
        set<int> candidates;
        set<int> new_candidates;
        vector<int> match_num(7,0);
        for (int i = 0; i < n; i++)
            candidates.insert(i);
        while (true) {
            int min_max_size = 1000000;
            int min_c = -1;
            vector<set<int>> min_match_set;
            if (candidates.size() == 1) {
                master.guess(words[*(candidates.begin())]);
                break;
            }
            for (int c = 0; c < n; c++) {
                fill(match_num.begin(), match_num.end(), 0);
                for (auto p: candidates) {
                    match_num[matches[c][p]]++;
                }
                int max_size = -1;
                for (int i = 0; i < 7; i++) {
                    if (match_num[i] > max_size) {
                        max_size = match_num[i];
                    }
                }
                if (max_size < min_max_size) {
                    min_max_size = max_size;
                    min_c = c;
                }
            }
            int match_l = master.guess(words[min_c]);
            if (match_l == 6) return;
            new_candidates.clear();
            for (auto p: candidates) {
                if (matches[min_c][p] == match_l) {
                    new_candidates.insert(p);
                }
            }
            candidates = new_candidates;
        }
    }
};