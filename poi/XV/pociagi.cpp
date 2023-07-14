#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_N = 1007, MAX_L = 107;
const long long B = 29, mod = 10000079;

int n, l, m, result[MAX_N], counter[mod], h[MAX_N], p[MAX_L];
char text[MAX_N][MAX_L];

int main() {
    scanf("%d%d%d", &n, &l, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", &text[i]);
        for(int j = l - 1; j >= 0; j--)
            h[i] = (h[i] * B + text[i][j] - 'a') % mod;
        counter[h[i]]++;
    }
    
    p[0] = 1;
    for(int i = 1; i <= l; i++)
        p[i] = (p[i - 1] * B) % mod;
    
    for(int i = 0; i < n; i++)
        result[i] = counter[h[i]];
    
    int p1, w1, p2, w2;
    while(m--) {
        scanf("%d%d%d%d", &p1, &w1, &p2, &w2);
        p1--; w1--; p2--; w2--;
        if(text[p1][w1] == text[p2][w2])
            continue;
        counter[h[p1]]--;
        if(p1 != p2)
            counter[h[p2]]--;
        h[p1] = (h[p1] + p[w1] * (text[p2][w2] - text[p1][w1] + mod)) % mod;
        h[p2] = (h[p2] + p[w2] * (text[p1][w1] - text[p2][w2] + mod)) % mod;
        swap(text[p1][w1], text[p2][w2]);
        counter[h[p1]]++;
        if(p1 != p2)
            counter[h[p2]]++;
        for(int i = 0; i < n; i++)
            result[i] = max(result[i], counter[h[i]]);
    }
    
    for(int i = 0; i < n; i++)
        printf("%d\n", result[i]);
    
    return 0;
}
