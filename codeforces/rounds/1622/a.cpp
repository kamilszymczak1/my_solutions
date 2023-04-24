#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    vector<int>l(3);
    for(int i = 0; i < 3; i++)
        cin >> l[i];
    sort(l.begin(), l.end());
    if(l[0] == l[1] && l[2] % 2 == 0) {
        cout << "YES\n";
    } else if(l[0] == l[2] && l[1] % 2 == 0) {
        cout << "YES\n";
    } else if(l[1] == l[2] && l[0] % 2 == 0) {
        cout << "YES\n";
    } else if(l[2] - l[0] == l[1]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        TestCase();
    }
    
    return 0;
}
