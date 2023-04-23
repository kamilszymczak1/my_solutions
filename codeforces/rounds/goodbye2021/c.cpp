#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    int result = n - 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            int difference = a[i] - a[j];
            int denominator = i - j;
            
            int current = n;
            for(int k = 0; k < n; k++) {
                if(a[k] * denominator == a[i] * denominator + (k - i) * difference) {
                    current--;
                }
            }
            result = min(result, current);
        }
    }
    cout << result  << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
