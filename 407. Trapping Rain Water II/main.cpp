#include <vector>
using namespace std;
struct Point {
    int r;
    int l;
    inline bool operator == (const Point & o) {
        return r == o.r && l == o.l;
    }
};
class UnionFind {
    vector<vector<Point>> parent;
public:
    UnionFind(int m, int n): parent(m){
        for (int i = 0; i < m; i++) parent[m].resize(n);
        for (int i = 0; i < m; i++) 
            for (int j = 0; j < n; j++)
                parent[i][j] = {i,j};
    }
    Point find(Point p) {
        while (!(parent[p.r][p.l] == p)) {
            auto &father = parent[p.r][p.l];
            parent[p.r][p.l] = parent[father.r][father.l];
            p = father;
        }
        return  p;
    }

    Point join(const Point & p1, const Point & p2) {
        Point set1 = find(p1);
        Point set2 = find(p2);
        if (!(set1 == set2)) {
            parent[set2.r][set2.l] = set1;
        }
    }

    bool sameSet(const Point & p1, const Point & p2) {
        Point set1 = find(p1);
        Point set2 = find(p2);
        return set1 == set2;
    }

};

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        vector<vector<int>> waterHeight;
        UnionFind uf(m,n);
        for (int r = 1; r < m - 1; r ++) {
            int left_most_h = heightMap[r][0];
            int left_most_p = 0;
            for (int l = 1; l < n - 1; l++) {
                waterHeight[r][l] = left_most_h;
                if (heightMap[r][l] >= left_most_h) {
                    left_most_h = heightMap[r][l];
                    left_most_p = l;
                } else {
                    if (l > left_most_p + 1) {
                        uf.join({r, l - 1}, {r, l});
                    }
                }
            }
            if (left_most_p != n - 2 && left_most_h > heightMap[r][n - 1]) {
                for (int i = left_most_p; i <= n - 2; i++) {
                    waterHeight[r][i] = heightMap[r][n - 1];
                }
            }
        }

        for (int l = 1; l < n - 1; l ++) {
            int top_most_h = heightMap[0][l];
            int top_most_p = 0;
            for (int r = 1; r < m - 1; r++) {
                if (top_most_h < waterHeight[r][l])
                    waterHeight[r][l] = top_most_h;
                if (heightMap[r][l] >= top_most_h) {
                    top_most_h = heightMap[r][l];
                    top_most_p = l;
                } else {
                    if (r > top_most_p + 1) {
                        uf.join({r - 1, l}, {r, l});
                    }
                }
            }
            if (top_most_p != m - 2 && top_most_h > heightMap[m - 1][l]) {
                for (int i = top_most_p; i <= m - 2; i++) {
                    if (waterHeight[i][l] >  heightMap[i][l]) 
                        waterHeight[i][l] = heightMap[i][l];
                }
            }
        } 
        for (int r = 1; r < m - 1; r ++)
            for (int l = 1; l < n - 1; l ++) {
                auto set = uf.find({r,l})
            }           
    }
};