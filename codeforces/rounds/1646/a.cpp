#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    long long n, s; cin >> n >> s;
    cout << s / (n * n) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
