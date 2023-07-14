#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n; unsigned long long x;
    scanf("%d%lld", &n, &x);
    char *s = new char[n + 1];
    scanf("%s", s);
    vector<char>S;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'U') {
            if(!S.empty() && S.back() != 'U') {
                S.pop_back();
            } else {
                S.push_back('U');
            }
        } else {
            S.push_back(s[i]);
        }
    }
    
    for(char c : S) {
        if(c == 'L') {
            x = x * 2;
        } else if(c == 'R') {
            x = x * 2 + 1;
        } else {
            x /= 2;
        }
    }
    
    printf("%lld\n", x);
    
    return 0;
}
