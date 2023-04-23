#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

bool Itr(long long a, long long b, long long c, long long d) {
    if(a > c) {
        swap(a, c);
        swap(b, d);
    }
    return c <= b; 
}


bool Check(long long x0, long long a, long long z0, long long c, long long y, long long k) {
    long long minX = x0 - a * k, maxX = x0 + a * k;
    long long minZ = - z0 - c * k - y, maxZ = - z0 + c * k - y;
    return Itr(minX, maxX, minZ, maxZ);
}

void TestCase() {
    int n; scanf("%d", &n);
    long long k; scanf("%lld", &k);
    vector<long long>a(n + 1), prefSum(n + 1);
    vector<int>prefZero(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        prefSum[i] = prefSum[i - 1] + a[i];
        prefZero[i] = prefZero[i - 1] + (a[i] == 0);
    }
    
    long long result = -1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            
            long long x0 = prefSum[i] - prefSum[0];
            long long y0 = prefSum[j] - prefSum[i];
            long long z0 = prefSum[n] - prefSum[j];
            
            long long a = prefZero[i] - prefZero[0];
            long long b = prefZero[j] - prefZero[i];
            long long c = prefZero[n] - prefZero[j];
            
            long long yMin = max(- z0 - x0 - k * (c + a), y0 - k * b);
            long long yMax = min(- z0 - x0 + k * (c + a), y0 + k * b);
            
            if(yMin <= yMax)
                result = max(result, max(abs(yMin), abs(yMax)) + 1);
            
        }
    }
    
    printf("%lld\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
