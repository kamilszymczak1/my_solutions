#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a) {
        scanf("%d", &x);
        while(x % 2 == 0)
            x /= 2;
    }
    multiset<int>b;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        b.insert(x);
    }
    sort(a.begin(), a.end());
    for(int i = n - 1; i >= 0; i--) {
        while(!b.empty() && b.find(a[i]) == b.end()) {
            auto it = b.end(); it--;
            if(*it != 1)
                b.insert(*it / 2);
            b.erase(it);
        }
        if(b.empty()) {
            printf("NO\n");
            return;
        }
        b.erase(b.find(a[i]));
    }
    printf("YES\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
