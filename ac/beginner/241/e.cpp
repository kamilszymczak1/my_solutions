#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    long long k; cin >> k;
    vector<int>a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<long long>sumAtFirstEntry(n, 0);
    vector<int>firstEntry(n, -1);
    long long result = 0, t = 0, ind = 0;
    while(k) {
        if(firstEntry[ind] == -1) {
            firstEntry[ind] = t;
            sumAtFirstEntry[ind] = result;
            result += a[ind];
            k--;
            ind = (ind + a[ind]) % n;
        } else {
            int cycleLen = t - firstEntry[ind];
            long long cycleSum = result - sumAtFirstEntry[ind];
            long long fullCycles = k / cycleLen;
            result += fullCycles * cycleSum;
            k -= cycleLen * fullCycles;
            for(int i = 0; i < n; i++)
                firstEntry[i] = -1;
        }
        t++;
    }
    
    cout << result << '\n';
    
    return 0;
}
