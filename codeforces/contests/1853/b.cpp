#include <iostream>
#include <vector>

using namespace std;

void test_case() {
    long long n, k; cin >> n >> k;
    if(n == 0) {
        cout << "1\n";
        return;
    }
    vector<long long>fib(2, 1);
    while(fib.back() < n) {
        int s = fib.size();
        fib.push_back(fib[s - 1] + fib[s - 2]);
    }
    
    int l = k - 3;
    int r = k - 2;
    
    if(l >= fib.size() || r >= fib.size()) {
        cout << "0\n";
        return;
    }
    
    int result = 0;
    for(long long a = 0; a * fib[l] <= n; a++) {
        if((n - a * fib[l]) % fib[r] == 0 && (n - a * fib[l]) / fib[r] >= a) {
            result++;
        }
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
