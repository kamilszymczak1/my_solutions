#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool Check(int len, int k, vector<int>cnt) {
    bool even = len % 2;
    if(even)
        len--;
    int j = 0;
    for(int i = 0; i < k; i++) {
        int x = len;
        while(x > 0 && j < 26) {
            if(cnt[j] > x) {
                cnt[j] -= x;
                x = 0;
            } else {
                //cnt[j] <= x
                if(cnt[j] % 2 == 0) {
                    x -= cnt[j];
                    cnt[j] = 0;
                } else {
                    x -= cnt[j] - 1;
                    cnt[j] = 1;
                }
                j++;
            }
        }
        if(x != 0)
            return false;
    }
    if(even) {
        int sum = 0;
        for(int i = 0; i < 26; i++)
            sum += cnt[i];
        return sum >= k;
    }
    return true;
}

void TestCase() {
    int k, n; cin >> n >> k;
    string s; cin >> s;
    vector<int>cnt(26, 0);
    for(char c : s)
        cnt[c - 'a']++;
    int result = 0;
    for(int i = 30; i >= 0; i--) {
        if(Check(result + (1 << i), k, cnt)) {
            result += 1 << i;
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
