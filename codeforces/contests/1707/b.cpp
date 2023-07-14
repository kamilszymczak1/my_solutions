#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    int zeroCount = 0;
    for(int i = 0; i < n; i++)
        zeroCount += a[i] == 0;
    if(zeroCount == n) {
        printf("0\n");
        return;
    }
    for(int i = zeroCount; i < n; i++)
        swap(a[i], a[i - zeroCount]);
    a.resize(n - zeroCount);
    while((int)a.size() + zeroCount > 1) {
        if(a.size() == 0)
            break;
        vector<int>b;
        if(zeroCount > 0) {
            zeroCount--;
            b.emplace_back(a[0]);
        }
        for(int i = 0; i < (int)a.size() - 1; i++)
            zeroCount += a[i] == a[i + 1];
        a.resize(unique(a.begin(), a.end()) - a.begin());
        for(int i = 0; i < (int)a.size() - 1; i++)
            b.emplace_back(a[i + 1] - a[i]);
        sort(b.begin(), b.end());
        swap(a, b);
    }
    if(a.empty())
        printf("0\n");
    else
        printf("%d\n", a[0]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
