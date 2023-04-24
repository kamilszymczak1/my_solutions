#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int ceil(int a, int b) {
    if(a % b == 0)
        return a / b;
    return a / b + 1;
}

void TestCase() {
    int n, m, k; cin >> n >> m >> k;
    
    if(n % m == 0) {
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < m; j++) {
                cout << n / m << ' ';
                for(int k = 0; k < n / m; k++) {
                    cout << (n / m) * j + k + 1 << ' ';
                }
                cout << '\n';
            }
        }
    } else {
        int K = m * ceil(n, m) - n;
        int nextPerson = 0;
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < m - K; j++) {
                cout << n / m + 1 << ' ';
                for(int k = 0; k < n / m + 1; k++) {
                    cout << nextPerson + 1 << ' ';
                    nextPerson = (nextPerson + 1) % n;
                }
                cout << '\n';
            }
            for(int j = 0; j < K; j++) {
                cout << n / m << ' ';
                for(int k = 0; k < n / m; k++) {
                    cout << (nextPerson + (n / m) * j + k) % n + 1 << ' ';
                }
                cout << '\n';
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
