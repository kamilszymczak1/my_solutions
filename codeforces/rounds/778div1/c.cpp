#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int Gen(long long w, map<long long, int>&m) {
    if(m.find(w) != m.end() && m[w] > 0) {
        m[w]--;
        return 1;
    }
    if(w == 1)
        return 1 << 20;
    long long result = Gen(w / 2, m);
    if(result >= (1 << 20))
        return 1 << 20;
    return result + Gen(w / 2 + (w % 2), m);
}

void TestCase() {
    int n; scanf("%d", &n);
    map<long long, int>m;
    vector<long long>a(n);
    long long w = 0;
    for(long long &x : a) {
        scanf("%lld", &x);
        m[x]++;
        w += x;
    }
    printf("%s\n", Gen(w, m) == n ? "Yes" : "No");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
