#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

void test_case() {
    int n, x, y; scanf("%d%d%d", &n, &x, &y);
    
    if(x * y != 0 || x + y == 0) {
        printf("-1\n");
        return;
    }
    
    if(x > y)
        swap(x, y);
    
    //x is zero
    
    if((n - 1) % y != 0) {
        printf("-1\n");
        return;
    }
    
    int player = 0;
    for(int i = 0; i < n - 1; i++) {
        //player vs i + 2
        if(i % y == 0)
            player = i + 1;
        printf("%d ", player + 1);
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
