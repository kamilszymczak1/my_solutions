#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    vector<int>a(n);
    for(auto &x : a)
        scanf("%d", &x);
    
    vector<bool>b(m, 1);
    for(int i = 0; i < n; i++) {
        int x = a[i] - 1;
        int y = m - a[i];
        if(x > y)
            swap(x, y);
        if(b[x] == 0) {
            b[y] = 0;
        } else {
            b[x] = 0;
        }
    }
    
    for(int i = 0; i < m; i++) {
        if(b[i]) {
            printf("B");
        } else {
            printf("A");
        }
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
