#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

class MedianFinder {
    multiset<int> nums;
    multiset<int>::iterator p1;
    multiset<int>::iterator p2;
    int nums_size = 0;
    bool before(multiset<int>::iterator p, const multiset<int>::iterator & t) {
        while (*p == *t) {
            if (p == t) {
                return true;
            }
            p++;
        }
        return false;
    }
public:
    MedianFinder() {
        nums.insert(-1000000);
        p1 = nums.begin();
        nums.insert(1000000);
        p2 = nums.begin();
        p2++;
        nums_size = 0;
    }
    
    void addNum(int num) {
        const multiset<int>::iterator & t = nums.insert(num);
        if (nums_size % 2 == 1) {
            if (num < *p1) {
                p1 --;
            } else if (num > *p1) {
                p2 ++;
            } else {
                if (before(p2, t)) {
                    p2++;
                } else {
                    p1--;
                }
            }
        } else {
            if (num < *p1) {
                p2 --;
            } else if (num == *p1) {
                if (!before(p1, t)) {
                    p2 --;
                } else if (num > *p2 || (num == *p2 && before(p2, t))) {
                    p1 ++;
                } else {
                    p1 = t;
                    p2 = t;
                }
            } else if (num > *p1 && num < *p2) {
                p1 = t;
                p2 = t;
            } else if (num == *p2) {
                if (before(p2, t)) {
                    p1 ++;
                } else {
                    p1 = t;
                    p2 = t;
                }
            } else if (num > *p2) {
                p1 ++;
            }
            
        }
        nums_size++;
    }
    
    double findMedian() {
        return ((double)*p1 + *p2) / 2;
    }
};

int main() {
    MedianFinder m;
    m.addNum(3);
    cout << m.findMedian() << endl;
    m.addNum(2);
    cout << m.findMedian() << endl;
    m.addNum(1);
    cout << m.findMedian() << endl;
    m.addNum(1);
    cout << m.findMedian() << endl;
    m.addNum(2);
    cout << m.findMedian() << endl;


}