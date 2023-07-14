#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void TestCase() {
    long long n; cin >> n;
    set<int>s;
    for(long long i = 1; i * i <= n; i++) {
        s.insert(i * i);
    }
    for(long long i = 1; i * i * i <= n; i++) {
        s.insert(i * i * i);
    }
    cout << s.size() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
