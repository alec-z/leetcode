#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;
class Solution {
 public:
  int MAX_N = 6;
  vector<int> strategies;
  vector<int> child_situation;
  Solution(int MAX_N)
      : MAX_N(MAX_N),
        strategies(pow(2, MAX_N), 0),
        child_situation(pow(2, MAX_N), -1) {}

  size_t set_to_number(vector<bool>& set) {
    size_t res = 0;
    for (int i = 1; i <= set.size() ; i++) {
      if (set[i - 1])
        res += pow(2, i - 1);
    }
    return res;
  }

  vector<int> number_to_set(size_t situation) {
    vector<int> situation_set(MAX_N, false);
    for (int i = 1; i <= MAX_N; i++) {
      if (situation & (size_t)(pow(2, i - 1))) {
        situation_set[i - 1] = true;;
      }
    }
    return situation_set;
  }

  void get_pre_must_win_situation(size_t cur_situation,
                                  vector<size_t>& pre_situations) {
   
    auto cur_situation_set = number_to_set(cur_situation);
    
    for (int s = 1; s <= MAX_N; s++) {
      if (cur_situation_set[s - 1] == false) {
        vector<bool> pre_situation_set(MAX_N, false);
        for (int i = 1; i <= MAX_N; i++) {
          if ((i - 1 == 0 || i - 1 == s || cur_situation_set[i - 1 - 1]) && 
            (i + 1 == MAX_N + 1 || i + 1 == s || cur_situation_set[i + 1 - 1])) {
              pre_situation_set[i - 1] = true;
            }
        }
        
        size_t pre_s = set_to_number(pre_situation_set);
        if (pre_s > 0 && strategies[pre_s] == 0) {
          strategies[pre_s] = s;
          child_situation[pre_s] = cur_situation;
          pre_situations.push_back(pre_s);
        }
      }
    }
  }
  void find_solution() {
    const size_t bottom_0 = 0b00001;
    const size_t bottom_1 = pow(2, MAX_N - 1);

    strategies[0] = 6;
    strategies[bottom_0] = 2;
    strategies[bottom_1] = MAX_N - 1;

    child_situation[bottom_0] = 0;
    child_situation[bottom_1] = 0;

    queue<size_t> q;

    q.push(bottom_0);
    q.push(bottom_1);
    while (!q.empty()) {
      size_t cur_situation = q.front();
      q.pop();
      vector<size_t> pre_situations(0);
      get_pre_must_win_situation(cur_situation, pre_situations);
      for (size_t pre_s : pre_situations) {
        q.push(pre_s);
        if (pre_s == pow(2, MAX_N) - 1) {
          size_t child = pre_s;
          while (child != 0) {
            cout << strategies[child] << " ";
            child = child_situation[child];
          }
        }
      }
    }
  }
};

int main() {
    for (int i = 5; i < 1000; i++) {
        Solution s(i);
        cout << "N = " << i << " :";
        s.find_solution();
        cout << endl;
    }   
        

}