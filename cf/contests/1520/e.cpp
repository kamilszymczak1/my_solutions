#include <iostream>

using namespace std;

constexpr int MAX_N = 1000007;
constexpr long long inf = 999999999999999999;

int change[MAX_N];

void TestCase() {
    int n, sheep = 0; string s;
    long long result = 0;
    long long sheepAtLeft = 0;
    cin >> n >> s;
    fill(change, change + n, 0);
    for(int i = 0; i < n; i++) {
        if(s[i] == '*') {
            change[i - sheep]++;
            result += i - sheep;
            sheep++;
        }
    }
    
    long long R = result;
    for(int i = 0; i + sheep <= n; i++) {
        sheepAtLeft += change[i];
        result += sheepAtLeft;
        result -= sheep - sheepAtLeft;
        R = min(result, R);
    }
    cout << R << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        TestCase();
    }
    
    return 0;
}
