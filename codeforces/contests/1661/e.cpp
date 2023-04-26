#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAX_N = 500'007;

char c[3][MAX_N];
int com[MAX_N], f[MAX_N * 3], pref[8][MAX_N], a[MAX_N];

int F(char c) {
    return c - '0';
}

int Find(int x) {
    return f[x] == x ? x : f[x] = Find(f[x]);
}

bool Union(int x, int y) {
    x = Find(x); y = Find(y);
    if(x == y)
        return false;
    f[x] = y;
    return true;
}

void TestCase() {
    int n; scanf("%d", &n); n++;
    for(int i = 0; i < 3; i++)
        scanf("%s", c[i] + 1);
    c[0][0] = c[1][0] = c[2][0] = '0';
    
    for(int i = 0; i < 3 * n; i++)
        f[i] = i;
    
    set<int>seven;
    
    for(int i = 1; i < n; i++) {
        a[i] = F(c[0][i]) + F(c[1][i]) * 2 + F(c[2][i]) * 4;
        if(a[i] == 7)
            seven.insert(i);
        pref[a[i]][i]++;
        for(int j = 0; j < 8; j++)
            pref[j][i] += pref[j][i - 1];
        
        com[i] += com[i - 1];
        for(int j = 0; j < 3; j++)
            com[i] += c[j][i] == '1';
        
        for(int j = 0; j < 3; j++) {
            if(c[j][i] == '0')
                continue;
            if(j != 0) {
                if(c[j - 1][i] == '1') {
                    com[i] -= Union(j * n + i, (j - 1) * n + i);
                }
            }
            if(j != 2) {
                if(c[j + 1][i] == '1') {
                    com[i] -= Union(j * n + i, (j + 1) * n + i);
                }
            }
            if(c[j][i - 1] == '1')
                com[i] -= Union(j * n + i, j * n + i - 1);
        }
    }
    
    int q; scanf("%d", &q);
    while(q--) {
        int l, r; scanf("%d%d", &l, &r);
        int ans = com[r];
        int type = a[l - 1] & a[l];
        if(type == 0) {
            printf("%d\n", com[r] - com[l - 1]);
        } else if(type != 5) {
            printf("%d\n", com[r] - com[l - 1] + 1);
        } else {
            auto itR = seven.lower_bound(l);
            int rightCnt = 2;
            if(itR != seven.end() && *itR <= r) {
                int R = *itR;
                if(pref[5][R - 1] - pref[5][l - 1] == R - l)
                    rightCnt = 1;
            }
            auto itL = seven.lower_bound(l);
            int leftCnt = 2;
            if(itL != seven.begin()) {
                itL--; int L = *itL;
                if(pref[5][l - 1] - pref[5][L] == l - L - 1)
                    leftCnt = 1;
            }
            
            int ans = com[r] - com[l - 1];
            if(rightCnt == 1 && leftCnt == 1)
                ans++;
            if(rightCnt == 2 && leftCnt == 2)
                ans += 2;
            if(leftCnt == 1 && rightCnt == 2)
                ans += 2;
            if(leftCnt == 2 && rightCnt == 1)
                ans += 2;
            
            printf("%d\n", ans);
        }
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
