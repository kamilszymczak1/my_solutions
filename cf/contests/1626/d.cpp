#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>cnt(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x - 1]++;
    }
    int result = 1 << 30;
    for(int first = 0; (1 << first) <= n; first++) {
        for(int second = 0; (1 << second) <= n; second++) {
            int here = 0;
            int i = 0, sum = 0;
            while(i < n && sum + cnt[i] <= (1 << first)) {
                sum += cnt[i];
                i++;
            }
            here += (1 << first) - sum;
            sum = 0;
            while(i < n && sum + cnt[i] <= (1 << second)) {
                sum += cnt[i];
                i++;
            }
            here += (1 << second) - sum;
            sum = 0;
            while(i < n) {
                sum += cnt[i];
                i++;
            }
            if(sum == 0) {
                here++;
            } else {
                int x = 1;
                while(x < sum)
                    x *= 2;
                here += x - sum;
            }
            result = min(result, here);
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
