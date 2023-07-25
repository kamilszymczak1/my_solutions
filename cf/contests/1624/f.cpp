#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
    return a == 0 ? b : gcd(b % a, a);
}

long long lcm(long long a, long long b) {
    return a * b / gcd(a, b);
}

void TestCase() {
    int n; cin >> n;
    long long result = 0, added = 0;
    long long lastAnswer = 0;
    for(int i = 9; i >= 0; i--) {
        if((1 << i) > n)
            continue;
        long long newResult = result + (1 << i) + added;
        long long newResultGood;
        if((newResult) % n == 0) {
            newResultGood = newResult;
        } else {
            newResultGood = newResult + n - (newResult % n);
        }
        if(newResultGood != newResult) {
            cout << "+ " << newResultGood - newResult << '\n' << flush;
            cin >> lastAnswer;
        }
        if(lastAnswer >= newResultGood / n)
            result = newResult - added;
        added += newResultGood - newResult;
    }
    cout << "! " << result + added << '\n' << flush;
}

int main() {
    ios_base::sync_with_stdio(0);
    TestCase();
    return 0;
}
