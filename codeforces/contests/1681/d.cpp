#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <cstring>

using namespace std;

int inf = 1 << 30;

int Get(long long x, vector<bool>&ok) {
    int result = 0;
    while(x) {
        ok[x % 10] = true;
        result++;
        x /= 10;
    }
    return result;
}

int Gen(long long x, int n, map<long long, int>&m) {
    if(m.find(x) != m.end())
        return m[x];
    vector<bool>ok(10, false);
    int len = Get(x, ok);
    
    if(len >= n) {
        return m[x];
    }
    int result = inf;
    for(int i = 2; i < 10; i++) {
        if(ok[i]) {
            result = min(result, Gen(x * i, n, m) + 1);
        }
    }
    return m[x] = result;
}

void TestCase() {
    long long n, x; scanf("%lld%lld", &n, &x);
    map<long long, int>m;
    int result = Gen(x, n, m);
    if(result == inf) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
