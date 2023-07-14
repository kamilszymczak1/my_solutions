#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

const int inf = 1 << 30;

void test_case() {
    int n, k, d, w; cin >> n >> k >> d >> w;
    int last_open_time = -inf;
    int doses_left = 0;
    
    vector<int>t(n);
    for(int i = 0; i < n; i++)
        cin >> t[i];
    
    int answer = 0;
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && j - i < k && t[i] + w + d >= t[j])
            j++;
        answer++;
        
        i = j - 1;
    }
    
    cout << answer << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
