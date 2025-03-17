#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        vector<int> count(26, 0);
        int i = 0;
        int j = 0;
        int len1 = s1.size();
        int len2 = s2.size();
        char c = 0;

        while (i < n1 * len1) {
            while ((--count[s2[j % len2] - 'a']) >= 0) {
                j++;
            }
            c = s2[j % len2];
            j++;
            while (i < n1 * len1 && s1[i % len1] != c) {
                count[s1[i % len1] - 'a'] ++;
                i++;
            } 
            if (i < n1 * len1) {
                count[s1[i % len1] - 'a'] ++;
                i++;
            }
        }
        return (j )  / len2 / n2;
    }
};

int main() {
    Solution s;
    s.getMaxRepetitions("baba", 11, "baab", 1);
}