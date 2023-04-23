#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const long long mod = 1'000'000'007;

vector<int>get_divisors(int x) {
    int i = 1;
    vector<int>answer;
    while(i * i < x) {
        if(x % i == 0) {
            answer.push_back(i);
            answer.push_back(x / i);
        }
        i++;
    }
    
    if(i * i == x)
        answer.push_back(i);
    return answer;
}

long long gcd(long long a, long long b) {
    while(b != 0) {
        long long c = a % b;
        a = b;
        b = c;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    int n; scanf("%d", &n);
    
    vector<int>phi(n + 1, 1), sieve(n + 1, -1);
    
    for(int i = 2; i <= n; i++) {
        if(sieve[i] == -1) {
            sieve[i] = i;
            for(long long j = 1ll * i * i; j <= n; j += i)
                sieve[j] = i;
        }
    }
    
    phi[1] = 1;
    
    for(int i = 2; i <= n; i++) {
        int d = sieve[i], j;
        for(j = i; j % d == 0; j /= d)
            phi[i] = phi[i] * d;
        phi[i] = (phi[i] / d) * (d - 1) * phi[j];
    }
    
    phi[1] = 0; //we change it because we want phi[i] to be the number of such pairs(x, y) such that x, y > 0, x is coprime with y and x + y = i    
    
    long long result = 0;
    
    for(int c = 1; c <= n - 2; c++) {
        
        vector<int>div = get_divisors(n - c);
        for(int d : div) {
            result = (result + lcm(c, d) * phi[(n - c) / d]) % mod;
        }
        
    }
    
    printf("%lld\n", result);
    
    return 0;
}
