#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

void DFT(vector<long long>&w, long long M, long long q) {
    int n = w.size(), msb = 0, log2 = 0;
    while((1 << (log2)) < n)
        log2++;
    vector<int>revBits(n);
    for(int i = 1; i < n; i++) {
        if(i & (1 << (msb + 1)))
            msb++;
        revBits[i] = revBits[i ^ (1 << msb)] | (1 << (log2 - msb - 1));
        if(revBits[i] < i)
            swap(w[i], w[revBits[i]]);
    }
    vector<long long>qPow(n, 1);
    for(int i = 1; i < n; i++)
        qPow[i] = (qPow[i - 1] * q) % M;
    for(int len = 2; len <= n; len *= 2) {
        for(int i = 0; i < n; i += len) {
            long long X = qPow[0], Y = qPow[n / 2];
            for(int j = 0; j * 2 < len; j++) {
                long long A = w[i + j], B = w[i + j + len / 2];
                w[i + j] = (A + X * B) % M;
                w[i + j + len / 2] = (A + Y * B) % M;
                X = (X * qPow[n / len]) % M;
                Y = (Y * qPow[n / len]) % M;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    long long N, M, q;
    cin >> N >> M >> q;
    vector<long long>a(N);
    for(auto &x : a)
        cin >> x;
    
    DFT(a, M, q);
    cout << accumulate(a.begin(), a.end(), 0ll) % M << '\n';
    for(int i = 1; i < N; i++)
        cout << a[i] << ' ';
    cout << a[0] << '\n';
    
    return 0;
}
