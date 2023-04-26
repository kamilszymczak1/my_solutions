#include <algorithm>
#include <iostream>
#include <array>

using namespace std;

const int MAX_N = 1e6;

long long arr[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n, k;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n >> k;
        for(int i = 0; i < n; i++)
            cin >> arr[i];
        sort(arr, arr + n, greater<int>());
        
        long long result = 0;
        for(int i = 0; i <= k; i++)
            result += arr[i];
        
        cout << result << "\n";
    }
}
