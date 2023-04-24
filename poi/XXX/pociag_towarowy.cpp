#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    vector<int>b(m);
    for(int i = 0; i < m; i++)
        scanf("%d", &b[i]);
    
    vector<int>left(1, -1), right(1, n);
    int p = 0;
    for(int x : b) {
        while(a[p] != x)
            p++;
        left.push_back(p);
        p++;
    }
    p = n - 1;
    reverse(b.begin(), b.end());
    for(int x : b) {
        while(a[p] != x)
            p--;
        right.push_back(p);
        p--;
    }
    reverse(right.begin(), right.end());
    reverse(b.begin(), b.end());
    
    vector<bool>answer(n, false);
    
    vector<set<int>>s(k + 1);
    for(int i = 0; i < n; i++)
        s[a[i]].insert(i);
    
    for(int i = 0; i < m; i++) {
        int l = left[i], r = right[i + 1];
        int x = b[i];
        auto it = s[x].upper_bound(l);
        while(it != s[x].end() && *it < r) {
            auto it2 = it; it2++;
            answer[*it] = true;
            s[x].erase(it);
            it = it2;
        }
    }
    
    for(int i = 0; i < n; i++)
        printf("%d ", (int)answer[i]);
    printf("\n");
    
    return 0;
}
