/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

#include <vector>
using namespace std;

class MountainArray {
  public:
    int get(int index);
    int length();
};

class Solution {
    int target;
    int len;
    vector<int> cached;

    int getIndex(MountainArray &mountainArr, int pos) {
        if (cached[pos] == -1) {
            cached[pos] = mountainArr.get(pos);
        }
        return cached[pos];
    }

    int tryFindM(MountainArray &mountainArr, int be, int en) {
        if (be > en) return -1;
        if (be == en) {
            if (getIndex(mountainArr, be) == target) return be;
            else return -1;
        }
        if (be + 1 == en) {
            if (getIndex(mountainArr, be) == target) return be;
            if (getIndex(mountainArr, be + 1) == target) return be + 1;
            return -1;
        }
        int mid = (be + en) / 2;
        
        int mid_value = getIndex(mountainArr, mid);
        int left_value = getIndex(mountainArr, mid - 1);
        if (mid_value > left_value) {
            if (mid_value == target) return mid;
            int left_pos = tryFindI(mountainArr, be, mid - 1);
            if (left_pos != -1)
                return left_pos;
            else 
                return  tryFindM(mountainArr, mid + 1, en);
        } else {
            int left_pos = tryFindM(mountainArr, be, mid - 1);
            if (left_pos != -1)
                return left_pos;
            else {
                if (mid_value == target) return mid;
                return tryFindD(mountainArr, mid + 1, en);
            }
        }
    }
    int tryFindI(MountainArray &mountainArr, int be, int en) {
        if (be > en) return -1;
        int mid = (be + en) / 2;
        int mid_value = getIndex(mountainArr, mid);
        if (mid_value == target) return mid;
        else if (target > mid_value) return tryFindI(mountainArr, mid + 1, en);
        else return tryFindI(mountainArr, be, mid - 1);
    }
    int tryFindD(MountainArray &mountainArr, int be, int en) {
        if (be > en) return -1;
        int mid = (be + en) / 2;
        int mid_value = getIndex(mountainArr, mid);
        if (mid_value == target) return mid;
        else if (target > mid_value) return tryFindD(mountainArr, be, mid - 1);
        else return tryFindD(mountainArr, mid + 1, en);
    }
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        this->target = target;
        this->len = mountainArr.length();
        cached.resize(len, -1);
        return tryFindM(mountainArr, 0, len -1);
    }
};