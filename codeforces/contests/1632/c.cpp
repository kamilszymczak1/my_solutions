#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

void TestCase() {
    int a, b; cin >> a >> b;
    int result = b - a;
    for(int i = a; i < b; i++) {
        if((i & b) == i) {
            result = min(result, i - a + 1);
        }
    }
    for(int i = b; i <= b * 2; i++) {
        if((a & i) == a) {
            result = min(result, i - b + 1);
        }
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
