import java.util.TreeMap;
class Solution {
    public int countRangeSum(int[] nums, int lower, int upper) {
        int n = nums.length;
        long[] openSums = new long[n + 1];
        long res = 0;
        openSums[0] = 0;
        for (int i = 1; i <= n; i++) openSums[i] = openSums[i - 1] + nums[ i - 1];
        TreeMap<Long, Long> intervalSums = new TreeMap<>();
        intervalSums.put(0L, 1L);
        for (int hi = 0; hi < n; hi++) {
            long s_hi = openSums[hi + 1];
            for (long c : intervalSums.subMap(s_hi - upper, s_hi - lower + 1L).values()) {
                res += c;
            }
            Long r = intervalSums.get(s_hi);
            if (r == null) {
                intervalSums.put(s_hi, 1L);
            } else {
                intervalSums.put(s_hi, r + 1);
            }
        }
        return (int)res;
    }
    public static void main(String[] args) {
        int[] nums = new int[] {-2,5,-1};
        int lower = -2, upper = 2;
        System.out.println(new Solution().countRangeSum(nums, lower, upper));
    }
}