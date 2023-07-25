#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <cstring>

using namespace std;

char c[200007];

bool Check(int ans, int n) {
    if(ans >= n)
        return true;
    int allOnes = 0;
    for(int i = 0; i < n; i++)
        allOnes += c[i] == '1';
    int ones = 0, zeroes = 0, end = -1;
    for(int beg = 0; beg < n; beg++) {
        while(end < n - 1 && zeroes + (c[end + 1] == '0') <= ans) {
            zeroes += c[end + 1] == '0';
            ones += c[end + 1] == '1';
            end++;
        }
        
        if(allOnes - ones <= ans)
            return true;
        
        zeroes -= c[beg] == '0';
        ones -= c[beg] == '1';
    }
    
    return false;
}

void TestCase() {
    scanf("%s", c);
    int n = strlen(c);
    int ans = -1;
    for(int bit = 19; bit >= 0; bit--) {
        ans += 1 << bit;
        if(Check(ans, n))
            ans -= 1 << bit;
    }
    printf("%d\n", ans + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
