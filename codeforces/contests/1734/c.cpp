#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

char c[1'000'007];

void test_case() {
    int n; scanf("%d", &n);
    
    vector<vector<int>>div(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j += i) {
            div[j].push_back(i);
        }
    }
    
    scanf("%s", c);
    
    vector<bool>valid(n + 1, true);
    long long result = 0;
    for(int i = 1; i <= n; i++) {
        if(c[i - 1] == '0') {
            for(int x : div[i]) {
                if(valid[x]) {
                    result += x;
                    break;
                }
            }
        } else {
            for(int x : div[i]) {
                valid[x] = false;
            }
        }
    }
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
