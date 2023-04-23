#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<long long>s(n);
    for(int i = 0; i < n; i++)
        cin >> s[i];
    
    if(n == 1) {
        cout << "Yes\n";
        cout << "0 0 " << s[0] << '\n';
        return 0;
    }
    if(n == 2) {
        cout << "Yes\n";
        cout << s[0] << " 0 0 " << s[1] << '\n';
        return 0;
    }
    
    long long minA[3] = {0, 0, 0};
    long long sumA[3] = {0, 0, 0};
    for(int i = 3; i < n + 2; i++) {
        long long j = i % 3;
        sumA[j] += s[i - 2] - s[i - 3];
        minA[j] = max(minA[j], -sumA[j]);
    }
    
    if(minA[0] + minA[1] + minA[2] <= s[0]) {
        cout << "Yes\n";
        minA[0] = s[0] - minA[1] - minA[2];
        cout << minA[0] << ' ' << minA[1] << ' ' << minA[2] << ' ';
        for(int i = 3; i < n + 2; i++) {
            int j = i % 3;
            minA[j] += s[i - 2] - s[i - 3];
            cout << minA[j] << ' ';
        }
        cout << '\n';
    } else {
        cout << "No\n";
    }
    
    return 0;
}
