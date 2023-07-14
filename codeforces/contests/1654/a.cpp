#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    sort(a.begin(), a.end());
    printf("%d\n", a[n - 1] + a[n - 2]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
