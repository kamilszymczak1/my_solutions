#include <iostream>

using namespace std;

const int MAX_N = 100;
int arr[MAX_N];
int n;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> arr[i];
        for(int i = n - 1; i >= 0; i--)
            cout << arr[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
