

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    for(int i = 0; i < n - 1; i++)
        if(a[i] == 0 && a[i + 1] == 0) {
            cout << "-1\n";
            return;
        }
        
        int h = 1;
    for(int i = 0; i < n; i++) {
        if(a[i] == 1) {
            if(i > 0 && a[i - 1] == 1)
                h += 5;
            else
                h++;
        }
    }
    cout << h << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
