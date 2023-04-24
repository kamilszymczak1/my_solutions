#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    int diff = 0;
    map<int, bool>present;
    for(int &x : a) {
        cin >> x;
        if(present[x] == false) {
            diff++;
            present[x] = true;
        }
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < diff; i++)
        cout << diff << ' ';
    for(int i = diff; i < n; i++)
        cout << i + 1 << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
