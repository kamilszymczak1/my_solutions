#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 1'000'007;

char a[MAX_N], b[MAX_N];
int pref[MAX_N];

const int A = 512;
vector<int>pos[A];

int Next(int a, char c) {
    auto it = lower_bound(pos[c].begin(), pos[c].end(), a + 1);
    if(it == pos[c].end())
        return -1;
    return *it;
}

int main() {
    scanf("%s%s", a, b);
    int n = strlen(a), m = strlen(b);
    for(int i = 0; i < n; i++)
        pos[a[i]].push_back(i);
    
    for(int i = 0; i < m; i++) {
        if(pos[b[i]].empty()) {
            printf("INF\n");
            return 0;
        }
    }
    
    int k = 0, currentPos = -1;
    while(k < m) {
        char c = b[k];
        auto it = lower_bound(pos[c].begin(), pos[c].end(), currentPos + 1);
        if(it == pos[c].end())
            break;
        currentPos = *it;
        k++;
    }
    
    if(k == m) {
        printf("0\n");
        return 0;
    }
    
    int t = pref[0] = -1;
    for(int i = 1; i <= n; i++) {
        while(t >= 0 && a[i - 1] != a[t])
            t = pref[t];
        pref[i] = ++t;
    }
    
    for(int i = 0; i <= n - pref[n]; i++)
        a[i] = a[i + pref[n]];
    n -= pref[n];
    for(int i = 0; i < A; i++)
        pos[i].clear();
    
    for(int i = 0; i < n; i++)
        pos[a[i]].push_back(i);
    
    int printed = 1;
    currentPos = -1;
    bool asf = 0;
    while(k < m) {
        char c = b[k];
        auto it = lower_bound(pos[c].begin(), pos[c].end(), currentPos + 1);
        if(it == pos[c].end()) {
            asf = true;
            printed++;
            currentPos = pos[c][0];
        } else {
            asf = false;

            currentPos = *it;
        }
        k++;
    }
    
    printf("%d\n", printed);
    
    return 0;
}
