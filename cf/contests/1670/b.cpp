#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <bitset>
#include <map>

using namespace std;

const int MAX_N = 100'007;
char s[MAX_N], c[MAX_N];

void TestCase() {
    int n; scanf("%d", &n);
    scanf("%s", s);
    int k; scanf("%d", &k);
    set<char>K;
    for(int i = 0; i < k; i++) {
        scanf("%s", c);
        K.insert(c[0]);
    }
    
    int result = 0;
    for(int i = 0; i < n; i++) {
        if(K.find(s[i]) == K.end())
            continue;
        int j = i - 1;
        while(j >= 0 && K.find(s[j]) == K.end())
            j--;
        //j is either one or -1
        if(j == -1) {
            result = max(result, i);
        } else {
            result = max(result, i - j);
        }
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
