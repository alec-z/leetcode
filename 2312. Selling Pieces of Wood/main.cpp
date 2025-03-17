#include <utility>
#include <vector>
using namespace std;
using Point = pair<int,int>;
class Solution {
  public:
    long long sellingWood(int m, int n, vector<vector<int>> &prices) {
        int height = m;
        int width = n;
        int price_n = prices.size();
        vector<vector<long long>> capacity(height + 1, vector<long long>(width + 1, 0));
        int p_n = 0;
        for (int i = 0; i < price_n; i++) {
            capacity[prices[i][0]][prices[i][1]] = max<long long>(capacity[prices[i][0]][prices[i][1]], prices[i][2]);
        }
        
        for (int h = 1; h <= height; h++) {
            for (int w = 1; w <= width; w++) {
                for (int ih = 1; ih <= h -1; ih++) {
                    capacity[h][w] = max<long long>(capacity[h][w], capacity[ih][w] + capacity[h-ih][w]);
                }
                for (int iw = 1; iw <= w -1; iw++) {
                    capacity[h][w] = max<long long>(capacity[h][w], capacity[h][iw] + capacity[h][w - iw]);
                }
            }
        }
        return capacity[height][width];
    }
};

int main() { 
    vector<vector<int>> prices = {{4,3,2},{5,3,16},{4,4,18},{8,7,6}};
    int m = 9;
    int n = 7;

    Solution s; 
    s.sellingWood( m,  n, prices);
    
    
}