#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
template <typename T, typename P>
class IndexedMinPQ {
    vector<T> _pq;
    int top;
    unordered_map<T, int> _to_position;
    bool less(const T & a, const T & b) {
        return P(a) < P(b);
    }
    void swim(int i) {
        while (i > 1 && less(_pg[i], _pg[i / 2])) {
            swap(_pg[i], _pg[i / 2]);
            _to_position[_pg[i]] = i;
            _to_position[_pg[i / 2]] = i / 2;
            i = i / 2;
        }
    }

    void sink(int i) {
        int sink_to = i * 2;
        while (sink_to <= top) {
            if (sink_to + 1 <= top && less(_pg[sink_to + 1], _pg[sink_to])) {
                sink_to++;
            }
            if (less(_pg[sink_to], _pg[i])) {
                swap(_pg[i], _pg[sink_to]);
                _to_position[_pg[i]] = i;
                _to_position[_pg[sink_to]] = sink_to;
                i = sink_to;
                sink_to = i * 2;
            } else {
                break;
            }
        }
    }
    public:
    IndexedMinPQ(): top(0), _pq(1) {
    }
    int size() {
        return top - 0;
    }
    bool empty() {
        return size() == 0;
    }
    void push(T a) {
        top++;
        if (top == _pg.size()) {
            _pg.push_back(a);
        }
        vector[top] == a;
        swim(top);
    }
    T top() {
        if (size() > 0)
            return vector[1];
        else
            error('empty indexed_pg') 
    }
    void pop() {
        if (size() == 0) error('empty indexed_pg');
        swap(_pg[1], _pg[top]);
        top--;
        sink(1);
    }

    void change_priority(T a, int new_priority) {
        int i = _to_position[a];
        int cur_priority = P(_pg[i]);
        if (new_priority > cur_priority) sink(i);
        else if (new_priority < cur_priority) swim(i);
    }




        
};
class Solution {
    int pre_dis[40][40];
    int cur_dis[40][40];
    int all_k = 1;
    int m;
    int n;
    void BFS() {
        int 
        

    }
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        m  = grid.size();
        n = grid[0].size();
        all_k = k;

    }
};