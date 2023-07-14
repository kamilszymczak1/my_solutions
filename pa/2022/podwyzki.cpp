#include <cstdio>
#include <vector>
#include <set>

using namespace std;

const int inf = 1 << 30;

int main() {
    int n, k; scanf("%d%d", &n, &k);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int x = n;
    for(int i = 0; i < n - 1; i++) {
        if(a[i] >= a[i + 1]) {
            x = min(x, i);
        }
    }
    
    if(x == n) {
        printf("NIE\n");
        return 0;
    }
    
    if(k > 3) {
        set<int>s;
        if(x != 0)
            s.insert(x);
        s.insert(x + 1);
        if(x + 2 != n)
            s.insert(x + 2);
        int t = 1;
        while((int)s.size() < k - 1) {
            s.insert(t);
            t++;
        }
        printf("TAK\n");
        for(int x : s)
            printf("%d ", x);
        printf("\n");
    } else {
        
        if(k == 2) {
            int mn_pref = a[0];
            vector<int>mx_suff(n);
            mx_suff[n - 1] = a[n - 1];
            for(int i = n - 2; i >= 0; i--)
                mx_suff[i] = max(mx_suff[i + 1], a[i]);
            for(int i = 0; i < n - 1; i++) {
                mn_pref = min(mn_pref, a[i]);
                if(mn_pref >= mx_suff[i + 1]) {
                    printf("TAK\n%d\n", i + 1);
                    return 0;
                }
            }
            printf("NIE\n");
            return 0;
        }
        
        //k == 3
        
        int mx = 0, mn = inf;
        for(int x : a) {
            mx = max(mx, x);
            mn = min(mn, x);
        }
        
        for(int i = 0; i < n; i++) {
            if(a[i] == mn && i != 0) {
                if(i == n - 1) {
                    printf("TAK\n%d %d\n", i, 1);
                    return 0;
                } else {
                    printf("TAK\n%d %d\n", i, i + 1);
                    return 0;
                }
            }
            if(a[i] == mx && i != n - 1) {
                if(i == 0) {
                    printf("TAK\n%d %d\n", i + 1, 2);
                    return 0;
                } else {
                    printf("TAK\n%d %d\n", i, i + 1);
                    return 0;
                }
            }
        }
        
        printf("NIE\n");
    }
    
    return 0;
}
