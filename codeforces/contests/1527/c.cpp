#include <iostream>
#include <map>

using namespace std;

void TestCase() {
    int n; cin >> n;
    map<int, long long>m;
    long long result = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        result += m[x] * (long long)(n - i);
        m[x] += i + 1;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
