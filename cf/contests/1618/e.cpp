#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    long long n; cin >> n;
    vector<long long>x(n);
    long long sum = 0;
    for(auto &y : x) {
        cin >> y;
        sum += y;
    }
    
    if(sum % (n * (n + 1) / 2) != 0) {
        cout << "NO\n";
        return;
    }
    
    long long sumOfAll = sum / (n * (n + 1) / 2);
    
    vector<long long>ans(n, -1);
    for(int i = 0; i < n; i++) {
        long long r = x[(i - 1 + n) % n] - x[i] + sumOfAll;
        if(r % n != 0 || r <= 0) {
            cout << "NO\n";
            return;
        }
        ans[i] = r / n;
    }
    cout << "YES\n";
    for(auto y : ans)
        cout << y << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    
    return 0;
}
