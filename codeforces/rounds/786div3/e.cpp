#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    int result = 1 << 30;
    for(int i = 0; i < n - 2; i++) {
        int diff = abs(a[i] - a[i + 2]);
        result = min(result, min(a[i], a[i + 2]) + diff / 2 + diff % 2);
    }
        
    for(int i = 0; i < n - 1; i++) {
        int x = a[i], y = a[i + 1];
        if(x > y)
            swap(x, y);
        int initMoves = y - x, allMoves = 0;
        if(initMoves * 2 >= y) {
            allMoves = y / 2 + y % 2;
        } else {
            y -= 2 * initMoves;
            x -= initMoves;
            allMoves = initMoves + (x + y) / 3 + ((x + y) % 3 != 0);
        }
        result = min(result, allMoves);
    }
    sort(a.begin(), a.end());
    result = min(result, a[0] / 2 + a[0] % 2 + a[1] / 2 + a[1] % 2);
    printf("%d\n", result);
    
    
    return 0;
}
