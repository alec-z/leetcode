#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>

using namespace std;

struct Question {
    int nums1_begin;
    int nums2_begin;
    int k;
    bool operator == (const Question o) const {
        return nums1_begin == o.nums1_begin &&
            (nums2_begin == o.nums2_begin) &&
            (k == o.k);
    }
};

template <>
struct std::hash<Question>
{
    std::size_t operator()( const Question& q ) const
    {
        // Compute individual hash values for first, second and third
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        res = res * 31 + hash<int>()( q.nums1_begin );
        res = res * 31 + hash<int>()( q.nums2_begin );
        res = res * 31 + hash<int>()( q.k );
        return res;
    }
};

class Solution {
private:
    vector<int>  nums1;
    vector<int>  nums2;
    unordered_map<Question, vector<int>> f_map;
    bool less(const vector<int> & v1, const vector<int> & v2) const {
        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] < v2[i]) {
                return true;
            } else if (v1[i] > v2[i]) {
                return false;
            }
        }
        return false;
    }
    vector<int>  max_number(Question q) {
        auto p = f_map.find(q);
        if (p != f_map.end()) return (*p).second;

        vector<int> max_res;
        if (q.k == 0) {
            return max_res;
        }
        
        int nums1_limit = (int)nums1.size() - max<int>(0,  q.k - 1 - ((int)nums2.size() - q.nums2_begin));
        int nums2_limit = (int)nums2.size() - max<int>(0,  q.k - 1 - ((int)nums1.size() - q.nums1_begin));
        int max_digit = -1;
        for (int i = q.nums1_begin; i < nums1_limit; i++) {
            max_digit = max<int>(max_digit, nums1[i]);
            if (max_digit == 9) break;
        }
        for (int i = q.nums2_begin; i < nums2_limit; i++) {
            max_digit = max<int>(max_digit, nums2[i]);
            if (max_digit == 9) break;
        }

        
        for (int i = q.nums1_begin; i < nums1_limit; i++) {
            if (nums1[i] == max_digit) {
                Question new_q {i + 1, q.nums2_begin, q.k - 1};
                auto tmp_res = max_number(new_q);
                if (max_res.size() == 0 || less(max_res, tmp_res)) {
                    max_res = tmp_res;
                }
                break;
            }
        }

        for (int i = q.nums2_begin; i < nums2_limit; i++) {
            if (nums2[i] == max_digit) {
                Question new_q {q.nums1_begin, i + 1, q.k - 1};
                auto tmp_res = max_number(new_q);
                if (max_res.size() == 0  || less(max_res, tmp_res)) {
                    max_res = tmp_res;
                }
                break;
            }
        }
        max_res.insert(max_res.begin(), max_digit);
        f_map[q] = max_res;
        return max_res;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        this->nums1 = nums1;
        this->nums2 = nums2;
        f_map.clear();
        vector<int> res;
        Question q{0, 0, k};
        return max_number(q);;
    }
};

int main() {
    Solution s;
    vector<int> nums1 {6,7};
    vector<int> nums2 {6,0,4};
    int k = 5;
    for (int d : s.maxNumber(nums1, nums2, k)) {
        cout << d << " ";
    }
    cout << endl;
}