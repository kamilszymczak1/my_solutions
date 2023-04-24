#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    int m = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    set<int>maxi;
    for(int i = 1; i < n - 1; i++) {
        if(a[i - 1] < a[i] && a[i] > a[i + 1]) {
            maxi.insert(i);
        }
    }
    
    for(auto it = maxi.begin(); it != maxi.end();) {
        auto next = it; next++;
        if(next == maxi.end())
            break;
        if(*it + 2 == *next) {
            a[*it + 1] = max(a[*it], a[*it + 2]);
            m++;
            next++;
            auto toErase = it; it++;
            maxi.erase(toErase);
            maxi.erase(it);
        }
        it = next;
    }
    
    for(auto x : maxi) {
        a[x - 1] = a[x];
        m++;
    }
    cout << m << '\n';
    for(int x : a)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
