#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    map<int, int>cnt;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        cnt[x]++;
    }
    
    int result = n * n;
    for(auto [key, q] : cnt) {
        int local = 0;
        while(q < n) {
            local += 1 + min(q, n - q);
            q *= 2;
        }
        result = min(result, local);
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
