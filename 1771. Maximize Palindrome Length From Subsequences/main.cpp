#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Solution {
    private:
    int internal_palindrome(string  word1, string word2) {
        int len1 = word1.size();
        int len2 = word2.size();
        string word = word1 + word2;
        int len = word.size();
        vector<vector<int>> res(len + 1, vector<int> (len  + 1, 0));
        vector<vector<int>> res2(len + 1, vector<int> (len  + 1, 0));
        int max_n = 0;
        for (int i  = len - 1; i >= 0; i--) {
            for (int j = i + 1; j <= len ; j++) {
                if (word[i] == word[j - 1]) {
                    int c = 1;
                    if (i < j - 1) c = 2; 
                    res[i][j] = max(res[i][j], res[i + 1][j - 1] + c);
                    if (i < len1 && j > len1){
                        res2[i][j] = max(res2[i][j], res[i][j]);
                        max_n = max(max_n, res2[i][j]);
                    }
                        
                } else {
                    res[i][j] = max(res[i][j], res[i][j - 1]);
                    res[i][j] = max(res[i][j], res[i + 1][j]);
                    res2[i][j] = max(res2[i][j], res2[i][j - 1]);
                    res2[i][j] = max(res2[i][j], res2[i + 1][j]);
                    max_n = max(max_n, res2[i][j]);
                }
            }
        }
        return max_n;
    }

public:
    int longestPalindrome(string word1, string word2) {
        int max_p = 0;
        max_p = internal_palindrome(word1, word2);
        return max_p;
    }
};

int main() {
    string word1 = "afaaadacb"; // “cfe" "fe"
    string word2 = "ca"; // "ef" "efc"
    Solution s;
    int c = s.longestPalindrome(word1, word2);
    cout << c;
}