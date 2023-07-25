#include <iostream>

using namespace std;

void TestCase() {
    long long k; cin >> k;
    long long column = 1;
    while(k > column * column - (column - 1) * (column - 1)) {
        k -= column * column - (column - 1) * (column - 1);
        column++;
    }
    
    long long row = min(k, column);
    long long cells = column * column - (column - 1) * (column - 1);
    if(k > column)
        column -= (k % column);
    cout << row << ' ' << column << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
