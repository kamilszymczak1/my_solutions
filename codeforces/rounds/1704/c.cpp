#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<int>a(m);
    for(int &x : a)
        scanf("%d", &x);
    sort(a.begin(), a.end());
    vector<int>s;
    for(int i = 0; i < m - 1; i++)
        s.push_back(a[i + 1] - a[i] - 1);
    s.push_back(a[0] - 1 + n - a.back());
    sort(s.begin(), s.end());
    reverse(s.begin(), s.end());
    int t = 0, result = 0;
    for(int x : s) {
        int filled = t * 2;
        x -= filled;
        if(x == 1)
            result++;
        else
            result += max(0, x - 1);
        
        t += 2;
    }
    printf("%d\n", n - result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
