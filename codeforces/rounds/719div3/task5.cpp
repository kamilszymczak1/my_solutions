#include <iostream>

using namespace std;

constexpr int MAX_N = 1000007;
constexpr long long inf = 999999999999999999;

int change[MAX_N];

void TestCase() {
    int n, sheeps = 0; string s;
    long long result = 0;
    long long sheepsAtLeft = 0;
    cin >> n >> s;
    fill(change, change + n, 0);
    for(int i = 0; i < n; i++) {
        if(s[i] == '*') {
            change[i - sheeps]++;
            result += i - sheeps;
            sheeps++;
        }
    }
    
    //cout << "init result = " << result << '\n';
    
    long long R = result;
    for(int i = 0; i + sheeps <= n; i++) {
        sheepsAtLeft += change[i];
        result += sheepsAtLeft;
        result -= sheeps - sheepsAtLeft;
        //cout << "i = " << i << ", result = " << result << '\n';
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
