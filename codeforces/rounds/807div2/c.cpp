#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

char s[300'000];

void TestCase() {
    int n, c, q; scanf("%d%d%d", &n, &c, &q);
    vector<pair<long long, long long>>op(c);
    vector<long long>len;
    len.push_back(n);
    scanf("%s", s);
    for(auto &[l, r] : op) {
        scanf("%lld%lld", &l, &r);
        l--; r--;
        len.push_back(len.back() + r - l + 1);
    }
    while(q--) {
        long long k; scanf("%lld", &k); k--;
        for(int i = c - 1; i >= 0; i--) {
            if(k < len[i])
                continue;
            long long offset = k - len[i];
            k = op[i].first + offset;
        }
        printf("%c\n", s[k]);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
