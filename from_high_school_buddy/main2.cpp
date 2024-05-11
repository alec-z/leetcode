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

  size_t set_to_number(set<int>& set) {
    size_t res = 0;
    for (int i : set) {
      res += pow(2, i - 1);
    }
    return res;
  }

  set<int> number_to_set(size_t situation) {
    set<int> situation_set;
    for (int i = 1; i <= MAX_N; i++) {
      if (situation & (size_t)(pow(2, i - 1))) {
        situation_set.insert(i);
      }
    }
    return situation_set;
  }

  void get_pre_must_win_situation(size_t cur_situation,
                                  vector<size_t>& pre_situations) {
    set<int> cur_situation_set, pre_situation_set, new_situation_set, tmp_set;
    cur_situation_set = number_to_set(cur_situation);
    for (int s = 1; s <= MAX_N; s++) {
      if (cur_situation_set.find(s) == cur_situation_set.end()) {
        set<int> set_with_s = cur_situation_set;
        set_with_s.insert(s);
        tmp_set.clear();
        for (auto i : set_with_s) {
          if (i > 1) {
            tmp_set.insert(i - 1);
          }
          if (i < MAX_N) {
            tmp_set.insert(i + 1);
          }
        }
        pre_situation_set.clear();
        for (auto i : tmp_set) {
          if (i == 1) {
            if (set_with_s.find(i + 1) != set_with_s.end())
              pre_situation_set.insert(i);
          } else if (i == MAX_N) {
            if (set_with_s.find(i - 1) != set_with_s.end())
              pre_situation_set.insert(i);
          } else {
            if (set_with_s.find(i - 1) != set_with_s.end() &&
                set_with_s.find(i + 1) != set_with_s.end())
              pre_situation_set.insert(i);
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