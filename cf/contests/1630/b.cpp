#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void TestCase() {
    int n, k; cin >> n >> k;
    vector<int>a(n), cnt(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    
    int bestBeg = 1, bestEnd = n;
    int end = 0, elementsIn = 0;
    for(int beg = 0; beg <= n; beg++) {
        end = max(end, beg - 1);
        while(end < n && 2 * elementsIn - n < k) {
            end++;
            elementsIn += cnt[end];
        }
        
        if(2 * elementsIn - n >= k && end - beg < bestEnd - bestBeg) {
            bestBeg = beg;
            bestEnd = end;
        }
        elementsIn -= cnt[beg];
    }
    
    for(int &x : a) {
        x = (bestBeg <= x && x <= bestEnd) ? 1 : -1;
    }
    
    stack<int>s;
    s.push(0);
    for(int i = 0; i < n; i++) {
        int j = i, sum = a[i];
        while(j < n - 1 && sum <= 0) {
            sum += a[++j];
        }
        while(sum <= 0) {
            sum++;
            s.pop();
        }
        s.push(j + 1);
        i = j;
    }
    while(s.size() > k + 1) {
        s.pop(); s.pop();
        s.push(n);
    }
    cout << bestBeg << ' ' << bestEnd << '\n';
    while(s.size() > 1) {
        int x = s.top(); s.pop();
        cout << s.top() + 1 << ' ' << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
