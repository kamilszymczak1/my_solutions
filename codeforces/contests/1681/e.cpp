#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <cstring>
#include <array>

using namespace std;


int main() {
    int n; scanf("%d", &n);
    
    vector<int>topDoor(n), rightDoor(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        topDoor[i] = b - 1;
        rightDoor[i] = c - 1;
    }
    
    vector<vector<array<array<long long, 2>, 2>>>jump(n);
    
    for(int i = 0; i < n - 2; i++) {
        jump[i].emplace_back();
        jump[i][0][0][0] = abs(topDoor[i] - topDoor[i + 1]) + 1;
        jump[i][0][0][1] = abs(i + 1 - topDoor[i]) + abs(i + 1 - rightDoor[i + 1]) + 1;
        jump[i][0][1][0] = abs(i + 1 - rightDoor[i]) + abs(i + 1 - topDoor[i + 1]) + 1;
        jump[i][0][1][1] = abs(rightDoor[i] - rightDoor[i + 1]) + 1;
    }
    
    for(int i = n - 1; i >= 0; i--) {
        for(int bit = 1; (1 << bit) + i < n - 1; bit++) {
            jump[i].emplace_back();
            int j = i + (1 << (bit - 1));
            jump[i][bit][0][0] = min(jump[i][bit - 1][0][0] + jump[j][bit - 1][0][0], jump[i][bit - 1][0][1] + jump[j][bit - 1][1][0]);
            jump[i][bit][0][1] = min(jump[i][bit - 1][0][1] + jump[j][bit - 1][1][1], jump[i][bit - 1][0][0] + jump[j][bit - 1][0][1]);
            jump[i][bit][1][0] = min(jump[i][bit - 1][1][0] + jump[j][bit - 1][0][0], jump[i][bit - 1][1][1] + jump[j][bit - 1][1][0]);
            jump[i][bit][1][1] = min(jump[i][bit - 1][1][1] + jump[j][bit - 1][1][1], jump[i][bit - 1][1][0] + jump[j][bit - 1][0][1]);
        }
    }
    
    
    int m; scanf("%d", &m);
    
    while(m--) {
        fflush(stdout);
        int row1, col1, row2, col2; scanf("%d%d%d%d", &row1, &col1, &row2, &col2);
        row1--; col1--; row2--; col2--;
        int i = max(row1, col1), j = max(row2, col2);
        if(i == j) {
            printf("%d\n", abs(row1 - row2) + abs(col1 - col2));
        } else {
            if(i > j) {
                swap(i, j);
                swap(row1, row2);
                swap(col1, col2);
            }
            
            long long d0 = abs(row1 - i) + abs(col1 - topDoor[i]);
            long long d1 = abs(col1 - i) + abs(row1 - rightDoor[i]);
            
            for(int bit = 19; bit >= 0; bit--) {
                if(i + (1 << bit) >= j)
                    continue;
                long long newD0 = min(d0 + jump[i][bit][0][0], d1 + jump[i][bit][1][0]);
                long long newD1 = min(d1 + jump[i][bit][1][1], d0 + jump[i][bit][0][1]);
                d0 = newD0;
                d1 = newD1;
                i += 1 << bit;
            }
            
            d0 += abs(topDoor[i] - col2) + abs(j - row2) + 1;
            d1 += abs(rightDoor[i] - row2) + abs(j - col2) + 1;
            
            printf("%lld\n", min(d0, d1));
        }
    }
    
    return 0;
}
