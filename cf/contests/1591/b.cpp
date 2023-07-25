#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    int result = 0, biggest = a[n - 1], j = n - 2;
    while(j >= 0) {
        if(a[j] > biggest) {
            result++;
            biggest = a[j];
        }
        j--;
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
