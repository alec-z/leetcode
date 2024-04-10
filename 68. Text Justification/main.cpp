#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
    string get_blank(int len) {
        string res = "";
        for (int i = 0; i < len; i++) {
            res += " ";
        }
        return res;
    }
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int words_len = words.size();
        int line_width = 0;
        int line_begin_pos = 0;
        vector<string> res;
        int i = 0;
        for (i = 0; i < words.size();) {
            string & word = words[i];
            if (line_width == 0) {
                line_width += word.size();
                i++;
            } else {
                if (line_width + word.size() + 1 > maxWidth) {
                    if (i - line_begin_pos == 1) {
                        res.push_back(words[line_begin_pos] + get_blank(maxWidth - words[line_begin_pos].size()));
                    } else if (i - line_begin_pos > 1) {
                        int remain_blanks = (maxWidth - line_width);
                        int all_blanks = remain_blanks / (i - line_begin_pos - 1) + 1;
                        int left_blanks = remain_blanks % (i - line_begin_pos - 1);
                        string line = words[line_begin_pos];
                        for (int j = line_begin_pos + 1; j <= i - 1; j++) {
                            if (j - line_begin_pos <= left_blanks) 
                                line += get_blank(all_blanks + 1);
                            else 
                                line += get_blank(all_blanks);
                            line += words[j];
                        }
                        res.push_back(line);
                    }
                    line_begin_pos = i;
                    line_width = 0;
                } else {
                    line_width += word.size() + 1;
                    i++;
                }
            }
        }
        string line = words[line_begin_pos];
        for (int j = line_begin_pos + 1; j < i; j++) {
            line += " " + words[j];
        }
        line += get_blank(maxWidth - line.size());
        res.push_back(line);
        return res;
    }  
};

int main() {
    Solution s;
    vector<string> words {
        "Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"
    };
    for (string &s : s.fullJustify(words, 20)) {
        cout << s << endl;
    }
}