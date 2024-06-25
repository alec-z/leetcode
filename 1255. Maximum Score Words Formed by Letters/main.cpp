#include <vector>
#include <string>
using namespace std;
using word_vector = vector<int>;
const int LETTER_SIZE = 26;
class Solution {
    
    bool less_than(const word_vector &s, const word_vector & u) {
        for (int i = 0; i < LETTER_SIZE; i++) {
            if (s[i] > u[i]) return false;
        }
        return true;
    }
    int get_score(const word_vector &s, vector<int> & score) {
        int total = 0;
        for (int i = 0; i < LETTER_SIZE; i++) {
            total += s[i] * score[i];
        }
        return total;
    }
    word_vector get_vector(const string & word) {
        word_vector res(LETTER_SIZE, 0);
        for (auto c: word) {
            res[c - 'a']++;
        }
        return move(res);
    }
    vector<word_vector> word_vectors;
    vector<int> scores;
    int n;
    int total_score;
    int max_score;
    word_vector cur_all_vector;
    word_vector upper_vector;
    void dfs(int level) {
        if (level < n) {
            for (int i = 0; i < LETTER_SIZE; i++) {
                cur_all_vector[i] += word_vectors[level][i];
            }
            if (less_than(cur_all_vector, upper_vector)) {
                total_score+=scores[level];
                if (total_score > max_score) max_score = total_score;
                dfs(level+1);
                total_score-=scores[level];
            }
            for (int i = 0; i < LETTER_SIZE; i++) {
                cur_all_vector[i] -= word_vectors[level][i];
            }
            dfs(level + 1);
        }
    }
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        n = words.size();
        total_score = 0;
        max_score = 0;
        cur_all_vector.resize(LETTER_SIZE, 0);
        for (auto & s: words) {
            word_vectors.push_back(get_vector(s));
            scores.push_back(get_score(word_vectors.back(), score));
        }
        upper_vector.resize(LETTER_SIZE, 0);
        for (int i = 0; i < letters.size(); i++)
            upper_vector[letters[i] - 'a']++;
        dfs(0);
        return max_score;
    }
};