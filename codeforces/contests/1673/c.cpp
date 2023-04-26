#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const long long mod = 1'000'000'007;
const int MAX_N = 40'001;

bool Palindromic(int x) {
    int rev = 0;
    for(int y = x; y; y /= 10)
        rev = rev * 10 + y % 10;
    return rev == x;
}

void TestCase() {
    
}

int main() {
    vector<long long>ways(MAX_N);
    ways[0] = 1;
    for(int i = 1; i < MAX_N; i++) {
        if(Palindromic(i)) {
            for(int j = 0; j + i < MAX_N; j++) {
                ways[j + i] += ways[j];
                if(ways[j + i] >= mod)
                    ways[j + i] -= mod;
            }
        }
    }
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        printf("%lld\n", ways[n]);
    }
    return 0;
}
