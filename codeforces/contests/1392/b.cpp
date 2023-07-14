#include <iostream>

#define MAX_N 200000
#define inf 2000000000

using namespace std;

int arr[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n;
    long long k;
    cin >> t;
    for(int j = 0; j < t; j++) {
        cin >> n >> k;
        int hi = -inf;
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
            hi = max(hi, arr[i]);
        }
        int newHi = -inf;
        for(int i = 0; i < n; i++) {
            arr[i] = hi - arr[i];
            newHi = max(arr[i], newHi);
        }
        if(k % 2 == 0)
            for(int i = 0; i < n; i++)
                arr[i] = newHi - arr[i];
            
            for(int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << "\n";
    }
    
    return 0;
}
