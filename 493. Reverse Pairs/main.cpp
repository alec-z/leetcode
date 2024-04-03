#include <vector>
#include <iostream>
using namespace std;


class Solution {
    int mergeSort(vector<int> & nums, vector<int> & aux, int lo, int hi) {
        if (lo == hi) return 0;
        int mid = (lo + hi) / 2;
        int res = 0;
        int left = mergeSort(nums, aux, lo, mid);
        int right = mergeSort(nums, aux, mid + 1, hi);
        int j = mid + 1;
        int i = lo;
        for (; i <= mid && j<=hi && (long)nums[i] <= (long)nums[j] * 2; i++) {
        }
        while (i <= mid && j <= hi) {
            res += mid - i + 1;
            j++;
            for (; i <= mid && j <= hi && (long)nums[i] <= (long)nums[j] * 2; i++) {
            }
        }
        i = lo;
        j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (j > hi) aux[k] = nums[i++];
            else if (i > mid) aux[k] = nums[j++];
            else if (nums[j] < nums[i]) aux[k] = nums[j++];
            else aux[k] = nums[i++];
        }
        for (int k = lo; k <= hi; k++) {
            nums[k] = aux[k];
        }
        return res + left + right;

    }
public:
    int reversePairs(vector<int>& nums) {
        vector<int> aux(nums.size());
        return mergeSort(nums, aux, 0, nums.size() - 1);
    }
};

int main() {
    Solution s;
    vector<int> nums {1,3,2,3,1};
    cout << s.reversePairs(nums) << endl;
}