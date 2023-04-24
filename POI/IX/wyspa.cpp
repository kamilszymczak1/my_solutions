

#include <iostream>

using namespace std;

const int MAX_N = 50007, LOG = 15;

int d[2 * MAX_N], n;

int len(int a, int b) {
    return d[b - 1] - d[a - 1];
}

int Best(int a, int b) {
    return min(len(a, b), len(b, a + n));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
        d[i + n] = d[i];
    }
    
    for(int i = 1; i <= 2 * n; i++)
        d[i] += d[i - 1];
    
    int result = 0;
    for(int i = 1; i <= n; i++) {
        int j = i + 1;
        for(int k = LOG; k >= 0; k--) {
            if(j + (1 << k) < i + n && Best(i, j + (1 << k)) >= Best(i, j + (1 << k) - 1)) {
                j += (1 << k);
            }
        }
        result = max(result, Best(i, j));
    }
    
    cout << result << '\n';
    
    return 0;
}
