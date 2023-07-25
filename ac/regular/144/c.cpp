#include <cstdio>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

int main() {
    int n, k; scanf("%d%d", &n, &k);
    if(2 * k > n) {
        printf("-1\n");
        return 0;
    }
    set<int>s;
    for(int i = 0; i < n; i++)
        s.insert(i);
    vector<int>v(n, -1);
    for(int i = 0; i < k; i++) {
        v[i] = i + k;
        s.erase(s.find(i + k));
    }
    int current = n - 1;
    for(int i = n - k - 1; n - 1 - current < k && current >= 2 * k; i--) {
        s.erase(s.find(current));
        v[i] = current--;
    }
    
    for(int i = 0; i < n; i++) {
        if(v[i] == -1) {
            auto it = s.begin();
            if(abs(i - *it) < k) {
                it = s.lower_bound(i + k);
            }
            v[i] = *it;
            s.erase(it);
        }
    }
    
    for(int x : v)
        printf("%d ", x + 1);
    printf("\n");
    
    return 0;
}
