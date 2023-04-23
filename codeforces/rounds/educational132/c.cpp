#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_N = 200'007;
char c[MAX_N], s[MAX_N];

void TestCase() {
    scanf("%s", c);
    int n = strlen(c);
    int left = 0, right = 0;
    for(int i = 0; i < n; i++) {
        left += c[i] == '(';
        right += c[i] == ')';
    }
    int leftmissing = n / 2 - left;
    int rightmissing = n / 2 - right;
    
    if(leftmissing == 0 || rightmissing == 0) {
        printf("YES\n");
        return;
    }
    
    for(int i = 0; i < n; i++) {
        if(c[i] == '?') {
            if(leftmissing != 0) {
                leftmissing--;
                s[i] = '(';
            } else {
                s[i] = ')';
                rightmissing--;
            }
        } else {
            s[i] = c[i];
        }
    }
    
   // printf("c = %s, s = %s\n", c, s);
    
    
    vector<int>sum(n);
    

    int hi = n - 1;
    while(c[hi] != '?' || s[hi] != '(')
        hi--;
    int j = 0;
    while(c[j] != '?' || s[j] != ')')
        j++;
    
    swap(s[hi], s[j]);
    
 //   printf("newS = %s\n", s);
    
    sum[0] = s[0] == '(' ? 1 : -1;
    for(int i = 1; i < n; i++) {
        sum[i] = sum[i - 1] + (s[i] == '(' ? 1 : -1);
    }
    
    if(*min_element(sum.begin(), sum.end()) < 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
