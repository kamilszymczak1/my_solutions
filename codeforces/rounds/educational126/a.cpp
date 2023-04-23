#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    for(int i = 0; i < n; i++) {
        if(a[i] > b[i])
            swap(a[i], b[i]);
    }
    long long ans = 0;
    for(int i = 0; i < n - 1; i++)
        ans += abs(b[i] - b[i + 1]) + abs(a[i] - a[i + 1]);
    printf("%lld\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
