#include <iostream>
#include <cmath>

using namespace std;

void TestCase() {
    long long n1, n2; cin >> n1;
    if(n1 & 1)
        n1++;
    n2 = n1;
    long long result1 = 0, result2 = 0;
    while(n1 >= 8 && n1 % 6 != 0) {
        n1 -= 8;
        result1 += 20;
    }
    while(n2 >= 10 && n2 % 6 != 0) {
        n2 -= 10;
        result2 += 25;
    }
    
    result1 += (long long)(ceil(n1 / 6.0) * 15);
    result2 += (long long)(ceil(n2 / 6.0) * 15);
    cout << min(result1, result2) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
