#include <iostream>

#define MAX_N 200000

using namespace std;

int arr[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n;
    cin >> t;
    for(int k = 0; k < t; k++) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> arr[i];
        long long result = 0;
        for(int j = n - 1; j > 0; j--) {
            if(arr[j] < arr[j - 1])
                result += arr[j - 1] - arr[j], arr[j] = arr[j - 1];
        }
        cout << result << "\n";
    }
    
    return 0;
}
