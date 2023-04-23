#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>
#include <set>

using namespace std;

int ceil(int a, int b) {
    int c = a / b;
    if(c * b == a)
        return c;
    return c + 1;
}

void test_case() {
    int n; scanf("%d", &n);
    vector<int>v(n);
    for(int &a : v)
        scanf("%d", &a);
    set<pair<int, int>>s;
    int result = 0;
    for(int i = 0; i < 30; i++) {
        
        for(int j = 0; j < n; j++) {
            if((v[k] & 1) == 0)
                continue;
            int k = j;
            while(k < n && (v[k] & 1) == (v[j] & 1))
                k++;
            
            if(s.find(make_pair(j, k)) == s.end()) {
                s.insert(make_pair(j, k));
                result += ceil(k - j, 2);
            }
            
            j = k - 1;
        }
        
        
        for(int j = 0; j < n; j++)
            v[i] /= 2;
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
