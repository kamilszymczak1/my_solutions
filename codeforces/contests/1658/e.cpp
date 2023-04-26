#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Tile {
    int x, y, cost;
    Tile() {}
    Tile(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
};

bool operator< (Tile &A, Tile &B) {
    return A.cost > B.cost;
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    vector<Tile>a(n * n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x; scanf("%d", &x);
            a[i * n + j] = Tile(i, j, x);
        }
    }
    sort(a.begin(), a.end());
    int mx1 = a[0].x + a[0].y, mn1 = a[0].x + a[0].y;
    int mx2 = a[0].x - a[0].y, mn2 = a[0].x - a[0].y;
    vector<vector<bool>>winning(n, vector<bool>(n, true));
    for(int i = 0; i < n * n; i++) {
        int p = a[i].x + a[i].y, q = a[i].x - a[i].y;
        if(abs(p - mx1) > k || abs(p - mn1) > k || abs(q - mx2) > k || abs(q - mn2) > k)
            winning[a[i].x][a[i].y] = false;
        if(winning[a[i].x][a[i].y]) {
            mx1 = max(mx1, p); mn1 = min(mn1, p);
            mx2 = max(mx2, q); mn2 = min(mn2, q);
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int p = i + j, q = i - j;
            if(abs(p - mx1) > k || abs(p - mn1) > k || abs(q - mx2) > k || abs(q - mn2) > k) {
                printf("G");
            } else {
                printf("M");
            }
        }
        printf("\n");
    }
    
    return 0;
}
