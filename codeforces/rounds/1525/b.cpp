#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n;
    cin >> n;
    vector<int>a(n, 0), ind(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        ind[a[i]] = i;
    }
    bool sorted = true;
    for(int i = 1; i < n; i++) {
        if(a[i] < a[i - 1])
            sorted = false;
    }
    
    if(sorted) {
        cout << "0\n";
        return;
    }
    if(ind[0] == n - 1 && ind[n - 1] == 0) {
        cout << "3\n";
        return;
    }
    cout << (ind[0] == 0 || ind[n - 1] == n - 1 ? "1" : "2") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        TestCase();
    }
}
