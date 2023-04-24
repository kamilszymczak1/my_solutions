#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <bitset>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    map<int, int>cnt;
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        cnt[a]++;
    }
    vector<int>v;
    int a = 0, b = 0;
    for(auto [x, c] : cnt) {
        if(c > 1) {
            a++;
        } else {
            b++;
        }
    }
    printf("%d\n", a + (b + 1) / 2);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
