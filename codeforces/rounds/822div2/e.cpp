#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<int>>a(n, vector<int>(n));
    vector<int>b(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    
    for(int i = 0; i < n; i++) {
        a[i][0] = 0;
        for(int j = 1; j < n; j++)
            a[i][j] = i * j % n;
    }

    for(int i = 0; i < n; i++) {
        int target_value = b[i];
        int current_value = a[i][i];
        
        int offset = (target_value - current_value + n) % n;
        
        for(int j = 0; j < n; j++)
            a[i][j] = (a[i][j] + offset) % n;
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int t = 1;
    while(t--)
        test_case();
}
