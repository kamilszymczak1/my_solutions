#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    map<int, int>cnt;
    for(int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        cnt[b[i]]++;
    }
    
    int r1 = 0, r2 = 0;
    for(int i = 0; i < n; i++) {
        r2 += cnt[a[i]];
        if(a[i] == b[i]) {
            r2--;
            r1++;
        }
    }
    
    printf("%d\n%d\n", r1, r2);
    
    return 0;
}
