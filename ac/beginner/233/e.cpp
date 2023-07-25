#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    string s; cin >> s;
    long long sum = 0;
    vector<long long>sums(s.size());
    sums[0] = s[0] - '0';
    for(int i = 1; i < s.size(); i++) {
        sums[i] = sums[i - 1] + (int)(s[i] - '0');
    }
    reverse(sums.begin(), sums.end());
    int remaining = 0;
    for(int i = 0; i < s.size() || remaining != 0; i++) {
        if(i == sums.size())
            sums.push_back(0);
        sums[i] += remaining;
        remaining = sums[i] / 10;
        sums[i] %= 10;
    }
    reverse(sums.begin(), sums.end());
    for(int x : sums)
        cout << x;
    cout << '\n';
    
    return 0;
}
