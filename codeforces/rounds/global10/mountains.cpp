#include <iostream>

#define MAX_N 1000000

using namespace std;

long long pref[MAX_N + 1];
long long h[MAX_N + 1];
long long mins[MAX_N + 1];

int main() {
    ios_base::sync_with_stdio(0);
    
    long long sumH = 0;
    int n;
    cin >> n;
    
    for(int i = 1; i <= n; i++) {
        cin >> h[i];
        sumH += h[i];
    }
    
    for(int i = n; i > 0; i--) {
        if(h[i] + 1 > h[i - 1])
            pref[i - 1] += h[i] - h[i - 1], mins[i] = 1;
    }
    
    for(int i = 0; i < n; i++)
        cout << h[i + 1] - mins[i + 1] + pref[i + 1] << " ";
    cout << "\n";
    
    return 0;
}
