#include <iostream>

using namespace std;

const long long inf = 1ll << 61;

long long Mult(long long a, long long b) {
    if(((__int128_t)a) * b > inf)
        return inf;
    return a * b;
}

long long Pow(long long x, int exp) {
    if(exp == 0)
        return 1;
    long long result = Pow(x, exp / 2);
    result = Mult(result, result);
    if(exp % 2 == 1)
        result = Mult(result, x);
    return result;
}

bool Sufficient(long long n, long long a, long long b, int k, long long sum) {
    sum += (b - a) * k;
    if(sum <= 0)
        return false;
    sum /= b;
    long long coeff = sum / k;
    sum %= k;
    long long product = Mult(Pow(coeff, k - sum), Pow(coeff + 1, sum));
    return product > n;
}

long long Solve(long long n, long long a, long long b) {
    long long result = inf;
    for(int k = 1; k < 65; k++) {
        long long beg = 0;
        for(int i = 60; i >= 0; i--) {
            beg += 1ll << i;
            if(Sufficient(n, a, b, k, beg))
                beg -= 1ll << i;
        }
        result = min(result, beg + 1);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    long long n, a, b; cin >> n >> a >> b;
    cout << Solve(n, a, b) << '\n';
    return 0;
}
