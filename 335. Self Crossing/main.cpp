#include <set>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

struct VerticalLine {
    int x;
    int y1;
    int y2;
};
struct HorizontalLine {
    int y;
    int x1;
    int x2;
};
struct Event {
    int type;
    int x;
    int y;
    int y1;
    int y2;
    int distance_index;
};

class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
        int x = 0, y = 0;
        vector<Event> events;
        for (int i = 0; i < distance.size(); i++) {
            int d = distance[i];  
            if (i % 4 == 0) {
                Event event{1, x, 0, y, y + d, i};
                y += d;
                events.push_back(event);  
            } else if (i % 4 == 1) {
                events.push_back(Event{0, x - d, y, 0, 0, i});
                events.push_back(Event{2, x, y, 0, 0, i});
                x -= d;
            } else if (i % 4 == 2) {
                Event event{1, x, 0, y - d, y, i};
                y -= d;
                events.push_back(event);
            } else {
                events.push_back(Event{0, x, y, 0, 0, i});
                events.push_back(Event{2, x + d, y, 0, 0, i});
                x += d;
            }
            
        }
        
        sort(events.begin(), events.end(), [](const Event &a, const Event &b) {return a.x < b.x || (a.x==b.x && a.type < b.type);});
        map<int, int> dots;
        for (int i = 0; i < events.size(); i++) {
            Event event = events[i];
            if (event.type == 0) {
                auto p = dots.find(event.y);
                if (p != dots.end()) return true;
                dots[event.y] = event.distance_index;
            } else if (event.type == 1) {
                auto p = dots.find(event.y1);
                int y1_index = 100000000;
                if (p != dots.end())  y1_index = (*p).second;
                if (abs(y1_index - event.distance_index) > 1) {
                    return true;
                }
                auto p = dots.find(event.y2);
                int y2_index = 100000000;
                if (p != dots.end())  y2_index = (*p).second;
                if (abs(y2_index - event.distance_index) > 1) {
                    return true;
                }
                auto p = dots.upper_bound(event.y1);
                if (p != dots.end() && (*p).first < event.y2) {
                    return true;
                }

            } else {
                dots.erase(dots.find(event.y));
            }
        }
        return false;
    }
};

int main() {
    vector<int> distance {1,1,2,1,1};
    Solution s;
    cout << s.isSelfCrossing(distance) << endl;

}