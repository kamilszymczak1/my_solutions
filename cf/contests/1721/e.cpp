#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <stack>
#include <bitset>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

const int MAX_N = 2'000'100;
const int A = 26;

char s[MAX_N], t[MAX_N];
int p[MAX_N], s_len = 0, t_len = 0;

int link[A][MAX_N];

int main() {
    scanf("%s", s);
    s_len = strlen(s);
    for(int i = s_len - 1; i >= 0; i--)
        swap(s[i], s[i + 1]);
    
    int k = p[0] = -1;
    
    for(int i = 1; i <= s_len; i++) {
        while(k >= 0 && s[k + 1] != s[i])
            k = p[k];
        p[i] = ++k;
    }
    
    for(int i = 0; i < A; i++)
        link[i][0] = -1;
    link[s[1] - 'a'][0] = 0;
    for(int i = 1; i < s_len; i++) {
        
        for(int j = 0; j < A; j++) {
            link[j][i] = link[j][p[i]];
        }
        link[s[i + 1] - 'a'][i] = i;
    }
    
    
    int q; scanf("%d", &q);
    while(q--) {
        scanf("%s", t);
        t_len = strlen(t);
        for(int i = 0; i < t_len; i++)
            s[i + s_len + 1] = t[i];
        
        int k = p[s_len];
        for(int i = s_len + 1; i <= s_len + t_len; i++) {
            while(k >= 0 && s[k + 1] != s[i]) {
                if(k < s_len - 1) {
                    k = link[s[i] - 'a'][k];
                } else {
                    k = p[k];
                }
            }
            p[i] = ++k;
        }
        
        for(int i = s_len + 1; i <= s_len + t_len; i++)
            printf("%d ", p[i]);
        printf("\n");
    }
}
