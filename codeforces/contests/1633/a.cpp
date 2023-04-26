#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int dist(int a, int b) {
    int result = 0;
    while(a) {
        if(a % 10 != b % 10)
            result++;
        a /= 10;
        b /= 10;
    }
    return result;
}

void TestCase() {
    int n; cin >> n;
    int digits = 0;
    for(int k = n; k; k /= 10) {
        digits++;
    }
    int result;
    if(digits == 2) {
        result = 14;
        for(int i = 14; i < 100; i += 7) {
            if(dist(n, result) > dist(n, i)) {
                result = i;
            }
        }
    } else {
        result = 105;
        for(int i = 105; i < 1000; i += 7) {
            if(dist(n, result) > dist(n, i)) {
                result = i;
            }
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
