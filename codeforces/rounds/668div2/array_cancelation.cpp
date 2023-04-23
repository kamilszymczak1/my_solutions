#include <iostream>

using namespace std;

const int MAX_N = 100000;
long long arr[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n;
    
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        cin >> n;
        long long totalSum = 0;
        long long positiveSum = 0;
        long long freeMoves = 0;
        
        for(int j = 0; j < n; j++) {
            cin >> arr[j];
            totalSum += abs(arr[j]);
            
            if(arr[j] >= 0)
                positiveSum += arr[j];
            else {
                int movesToMake = min(positiveSum, abs(arr[j]));
                freeMoves += movesToMake;
                positiveSum -= movesToMake;
            }
        }
        
        cout << totalSum / 2 - freeMoves << "\n";
    }
    
    
    
    return 0;
}
