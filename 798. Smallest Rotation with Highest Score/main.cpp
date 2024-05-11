#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int bestRotation(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> count;
        count.reserve(nums.size() * 2);
        int score = 0;
        for (int i = 0; i < n; i++) {
            nums[i] = i - nums[i];
            count[nums[i]] = count[nums[i]] + 1;
            if (nums[i] >= 0) score++;
        }
        int max_score = score;
        int max_k = 0;
        for (int k = 1; k < n; k++) {
            auto & p = nums[k - 1];
            count[p]--;
            if (p >= k - 1)
                score --;    
            p += n;
            count[p]++;
            if (p >= k - 1) 
                score ++;
            score -= count[k - 1];
            if (score > max_score) {
                max_score = score;
                max_k = k;
            }
        }
        return max_k;
    }
};
