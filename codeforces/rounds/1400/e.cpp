#include <iostream>
#include <vector>

#define MAX_N (int)5000
#define inf (int)1e9 + 10

using namespace std;

int arr[MAX_N];
int Calc(int a, int b);

int main() {
    ios_base::sync_with_stdio(0);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    int result = Calc(0, n);
    cout << result << "\n";
    
    return 0;
}

int Calc(int a, int b) {
    if(a >= b)
        return 0;
    int lo = inf;
    for(int i = a; i < b; i++)
        lo = min(arr[i], lo);
    vector<int>zeros;
    for(int i = a; i < b; i++)
        if(arr[i] == lo)
            zeros.push_back(i);
        
        int result1 = b - a;
    
    
    for(int i = a; i < b; i++)
        arr[i] -= lo;
    int result2 = Calc(a, zeros[0]) + Calc(zeros.back() + 1, b) + lo;
    for(int i = 0; i < zeros.size() - 1; i++)
        result2 += Calc(zeros[i] + 1, zeros[i + 1]);
    return min(result1, result2);
}
