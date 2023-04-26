#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    vector<int>v;
    for(int len = 1; len <= 9; len++) {
        for(int digit = 1; digit <= 9; digit++) {
            int number = 0;
            for(int i = 0; i < len; i++) {
                number = number * 10 + digit;
            }
            v.push_back(number);
        }
    }
    sort(v.begin(), v.end());
    
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        auto it = upper_bound(v.begin(), v.end(), n);
        cout << it - v.begin() << '\n';
    }
    
    
    return 0;
}
