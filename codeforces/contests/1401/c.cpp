#include <algorithm>
#include <iostream>

#define MAX_N 100000

using namespace std;

int GCD(int a, int b);

int n, a[MAX_N], s[MAX_N];
bool good[MAX_N];
bool Query();

int main() {
    ios_base::sync_with_stdio(0);
    
    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
        if(Query())
            cout << "YES\n";
        else
            cout << "NO\n";
        return 0;
}

bool Query() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        s[i] = a[i];
    }
    sort(s, s + n); 
    for(int i = 0; i < n; i++)
        if(a[i] != s[i] && (a[i] % s[0] != 0))
            return false;
        return true;
}

int GCD(int a, int b) {
    if(a < b)
        swap(a, b);
    
    while(b != 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}
