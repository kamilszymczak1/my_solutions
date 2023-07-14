#include <algorithm>
#include <iostream>

#define MAX_N 100000

using namespace std;

long long arr[MAX_N];
const long long maxVal = 10000000000000;
int n;

long long pow(long long base, int exp) {
    if(exp == 0)
        return 1;
    if(exp == 1)
        return base;
    long long result = pow(base, exp / 2);
    result = result * result;
    if(exp % 2 != 0)
        result = result * base;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n;
    
    long long sum = 0;
    long long result = 0;
    
    for(int i = 0; i < n; i++)
        cin >> arr[i], sum += arr[i];
    
    sort(arr, arr + n);
    
    if(n > 50)
        result = sum - n;
    else {
        for(int base = 1; pow(base, n - 1) < maxVal; base++) {
            long long currResult = 0;
            long long currPow = 1;
            for(int i = 0; i < n; i++)
                currResult += abs(arr[i] - currPow), currPow *= base;
            if(base == 1)
                result = currResult;
            else
                result = min(result, currResult);
        }
    }
    
    cout << result << "\n";
    
    return 0;
}
