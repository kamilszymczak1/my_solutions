#include <cstdio>
#include <vector>

using namespace std;

long long ceil(long long a, long long b) {
    if(a % b == 0)
        return a / b;
    return a / b + 1;
}

bool Check(vector<long long>&v, long long a, long long b, long long c) {
    long long aOp = 0, bOp = 0;
    for(long long &x : v) {
        if(x < c) {
            aOp += ceil(c - x, a);
        } else {
            bOp += (x - c) / b;
        }
    }
    return bOp >= aOp;
}

int main() {
    int n; scanf("%d", &n);
    long long a, b; scanf("%lld%lld", &a, &b);
    vector<long long>v(n);
    for(auto &x : v)
        scanf("%lld", &x);
    
    long long result = 0;
    for(int bit = 30; bit >= 0; bit--) {
        result += (1ll << bit);
        if(Check(v, a, b, result) == false)
            result -= 1ll << bit;
    }
    
    printf("%lld\n", result);
    
    return 0;
}
