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

char s1[300'000], s2[300'000];

vector<pair<int, int>> Islands(char *c, int n) {
    vector<pair<int, int>>result;
    for(int i = 0; i < n; i++) {
        if(c[i] == '0')
            continue;
        int j = i;
        while(j < n && c[j] == '1')
            j++;
        result.emplace_back(i, j - 1);
        i = j - 1;
    }
    return result;
}

void TestCase() {
    int n; scanf("%d", &n);
    scanf("%s%s", s1, s2);
    
    if(s1[0] != s2[0] || s1[n - 1] != s2[n - 1]) {
        printf("-1\n");
        return;
    }
    vector<pair<int, int>>i1, i2;
    i1 = Islands(s1, n);
    i2 = Islands(s2, n);
    
    if(i1.size() != i2.size()) {
        printf("-1\n");
    } else {
        long long result = 0;
        for(int i = 0; i < (int)i1.size(); i++) {
            result += abs(i1[i].first - i2[i].first);
            result += abs(i1[i].second - i2[i].second);
        }
        printf("%lld\n", result);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
