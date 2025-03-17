#include <vector>
using namespace std;
class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        
    }
};

struct Collide {
    double time;
    int pre_car;
};

class IndexPriorityQuery {
    vector<Collide> arr;
    vector<int> car_t_l;
    int len;
    IndexPriorityQuery(int n): arr(n + 1), car_t_l(n) {
        len = n;
    }
    void insert(Collide c) {
        arr[++len] = c;
        car_t_l[c.pre_car] = len;
        swim(len);
    }
    Collide top() {
        return arr[1];
    }
    Collide remove(int pre_car) {
        int l = car_t_l[pre_car];
        car_t_l[pre_car] = -1;
        car_t_l[arr[len].pre_car] = l;
        swap(arr[l], arr[len--]);
        sink(l);
    }
    void update(int pre_car, double time) {
        int l = car_t_l[pre_car];
        if (time > arr[l].time) {
            arr[l].time = time;
            sink(l);
        } else {
            arr[l].time = time;
            swim(l);
        }

    }
    private:
    void sink(int i) {
        while (2 * i <= len) {
            int j = 2 * i;
            if (j + 1 <= len && arr[j + 1].time < arr[j].time) j++;
            if (arr[i].time < arr[j].time) {
                break;
            }
            swap(arr[i], arr[j]);
            swap(car_t_l[arr[i].pre_car], car_t_l[arr[j].pre_car]);
            i = j;
        }
    }
    void swim(int i) {
        while (i > 1 && arr[i].time < arr[i / 2].time) {
            swap(arr[i], arr[i / 2]);
            swap(car_t_l[arr[i].pre_car], car_t_l[arr[i / 2].pre_car]);
            i = i / 2;
        }
    }
};