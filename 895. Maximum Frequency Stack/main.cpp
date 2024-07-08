#include <unordered_map>
#include <map>
#include <stack>
using namespace std;

class FreqStack {
    unordered_map<int, int> map_v_f;
    map<int, stack<int>> map_f_v;
    int insert_times;
public:
    FreqStack(): map_v_f(), map_f_v() {
    }
    
    void push(int val) {
        int f = map_v_f[val];
        f++;
        map_v_f[val] = f;
        map_f_v[f].push(val);
    }
    
    int pop() {
        auto p = map_f_v.rbegin();
        auto & most_f_stack = p->second;
        int f = p->first;
        
        int val = most_f_stack.top();
        most_f_stack.pop();
        if (most_f_stack.empty()) {
            map_f_v.erase(f);
        }
        map_v_f[val] = f - 1;
        return val;
    }
};
