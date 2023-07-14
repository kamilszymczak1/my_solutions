#include <iostream>

#define MAX_N 100000

using namespace std;

long long arr[MAX_N];
int n;

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    if(n == 1) {
        cout << "1 1\n" << -arr[0] << "\n1 1\n0\n1 1\n0\n";
        return 0;
    }
    
    cout << 1 << " " << n << "\n";
    for(int i = 0; i < n; i++) {
        long long prev = arr[i];
        long long rem = abs(arr[i]) % (n - 1);
        long long mult = n - 1 - rem;
        if(arr[i] < 0)
            mult = -mult;
        cout << mult * n << " ";
        arr[i] += mult * n;
    }
    cout << "\n" << 1 << " " << n - 1 << "\n";
    for(int i = 0; i < n - 1; i++)
        cout << -arr[i] << " ";
    cout << "\n" << n << " " << n << "\n";
    cout << -arr[n - 1] << "\n";
    
    return 0;
}
