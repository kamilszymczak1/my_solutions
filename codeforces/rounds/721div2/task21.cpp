#include <iostream>

using namespace std;

void TestCase() {
    int n; cin >> n;
    string s; cin >> s;
    int cz = 0;
    for(auto x : s)
        if(x == '0')
            cz++;
        
    if(cz % 2 == 1) {
        cout << "ALICE\n";
    } else {
        //bob can make a draw
        if(cz % 4 != 0) {
            cout << "BOB\n";
        } else {
            cout << "DRAW\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
