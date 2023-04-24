#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <cstring>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    int pos = 0;
    int m; scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int b; scanf("%d", &b);
        pos = (pos + b) % n;
    }
    printf("%d\n", a[pos]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}

