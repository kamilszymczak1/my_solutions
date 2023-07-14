#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, k; cin >> n >> k;
    if(k <= (n / 2) + (n % 2)) {
        vector<vector<char>>grid(n, vector<char>(n, '.'));
        for(int i = 0; i < k; i++)
            grid[i * 2][i * 2] = 'R';
        for(vector<char>&v : grid) {
            for(char c : v) {
                cout << c;
            }
            cout << '\n';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
