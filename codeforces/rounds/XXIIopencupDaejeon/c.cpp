#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int>a(1 << n);
    for(int &x : a)
        scanf("%d", &x);
    
    for(int i = 0; i < (1 << n); i++) {
        for(int j = 0; j < n; j++) {
            for(int k = j; k < n; k++) {
                int x = i | (1 << j);
                int y = i | (1 << k);
                
                if(a[x] + a[y] < a[x & y] + a[x | y]) {
                    printf("%d %d\n", x, y);
                    return 0;
                }
            }
        }
    }
    
    printf("-1\n");
    
    return 0;
}
