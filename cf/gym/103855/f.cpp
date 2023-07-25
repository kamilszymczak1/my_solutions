#include <cstdio>
#include <vector>
#include <algorithm>
    
using namespace std;
    
const int MAX_N = 300'007;
    
char c[MAX_N];
    
int main() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    vector<long long>a(n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    
    vector<long long>b;
    for(int i = 0; i < n; i++) {
        int j = i;
        long long hi = a[i];
        while(j < n && c[i] == c[j]) {
            hi = max(hi, a[j]);
            j++;
        }
        b.push_back(hi);
        i = j - 1;
    }
    
    long long sum = 0;
    vector<long long>c;
    for(int i = 1; i < (int)b.size() - 1; i++) {
        sum += b[i];
        c.push_back(b[i]);
    }
    sort(c.begin(), c.end()); 
    for(int i = 0; i < (int)c.size() / 2; i++)
        sum -= c[i];
    printf("%lld\n", sum);
    
    
    return 0;
}
