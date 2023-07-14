#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>A(n);
    for(int &x : A)
        cin >> x;
    int i = 0;
    while(i < n - 1 && A[i] <= A[i + 1])
        i++;
    int X = A[i];
    
    for(int x : A) {
        if(x != X) {
            cout << x << ' ';
        }
    }
    cout << '\n';
    
    return 0;
}
