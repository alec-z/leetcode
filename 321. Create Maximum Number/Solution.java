
class Solution {
    private boolean less(int[] nums1, int nums1_begin, int[] nums2, int nums2_begin) {
        int i = nums1_begin, j = nums2_begin, n1 = nums1.length, n2 = nums2.length;
        while (i < n1 && j < n2) {
            if (nums1[i] < nums2[j]) {
                return true;
            } else if (nums1[i] > nums2[j]) {
                return false;
            } else {
                i++;
                j++;
            }
        }
        if (i == n1 && j < n2) {
            return true;
        }
        return false;
    }
    private int[] merge(int[] nums1, int[] nums2) {
        int l1 = nums1.length, l2 = nums2.length;
        int[] res = new int[l1 + l2];
        int i = 0, j = 0, k = 0;
        while (i < l1 || j < l2) {
            if (less(nums1, i, nums2, j)) {
                res[k++] = nums2[j++];
            } else {
                res[k++] = nums1[i++];
            }
        }
        return res;
    }
    private int[] singleMaxNumber(int[] nums, int k) {
        int[] res = new int[k];
        int start = 0, i, limit, max_digit, p = 0;
        while (k > 0) {
            limit = nums.length - (k - 1);
            max_digit = -1;
            for (i = start; i < limit; i++) {
                max_digit = Math.max(max_digit, nums[i]);
            }
            res[p++] = max_digit;
            k--;
            for (i = start; i < limit; i++) {
                if (nums[i] == max_digit) {
                    break;
                }
            }
            start = i + 1;
        }
        return res;
    }
    public int[] maxNumber(int[] nums1, int[] nums2, int k) {
        int[] res = new int[k];
        for (int l = 0; l <= k; l++) {
            if (l > nums1.length || k - l > nums2.length) continue;
            int[] part1 = singleMaxNumber(nums1, l);
            int[] part2 = singleMaxNumber(nums2, k - l);
            int[] all_part = merge(part1, part2);
            if (less(res,0, all_part,0)) {
                res = all_part;
            }
        }
        return res;
    }
    public static void main(String[] args) {
        int[] nums1 = new int[]{2,5,6,4,4,0}, nums2 = new int[]{7,3,8,0,6,5,7,6,2};
        Solution s = new Solution();
        for (int i : s.maxNumber(nums1, nums2, 15)) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}