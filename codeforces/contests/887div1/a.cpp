#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <bitset>

using namespace std;
void test_case() {
    int n; cin >> n;
    long long k; cin >> k;
    vector<long long>a(n);
    for(long long &x : a)
        cin >> x;
    if(a[0] != 1) {
        cout << "1\n";
        return;
    }
    
    long long pos = 1;
    long long jump = 1;
    int ind = 1;
    for(int i = 0; i < k; i++) {
        pos += jump;
        while(ind < n && a[ind] <= pos) {
            jump++;
            pos++;
            ind++;
        }
    }
    cout << pos << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
