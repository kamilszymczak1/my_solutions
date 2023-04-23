#include <iostream>
#include <algorithm>

#define MAX_N 100000

using namespace std;

int arr[MAX_N];
int beg = 0;
int end = 0;
int mid = 0;

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> d >> m;
    
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
    sort(arr, arr + n);
    
    beg = 0;
    end = n - 1;
    mid = n - 1;
    
    for(int i = 0; i < n; i++)
        if(arr[i] > m) {
            mid = i;
            break;
        }
    
    
    long long lessSum = 0;
    for(int i = 0; i < d; i++)
        if(i >= n)
            break;
        else
            lessSum += arr[i];
        
    long long result = 0;
    
    for(int i = 0; i < n; i++) {
        if(lessSum >= arr[end]) {
            lessSum -= arr[beg];
            result += arr[beg++];
            lessSum += end - beg + 1 >= d ? arr[beg + d] : 0;
        } else {
            
        }
    }
    
    cout << result << "\n";
    
    return 0;
}
