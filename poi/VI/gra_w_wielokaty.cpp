#include <algorithm>
#include <iostream>

using namespace std;

bool IsExterior(int *arr, int n);

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, arr[3];
    
    cin >> n;
    
    for(int i = 0; i < 3; i++)
        cin >> arr[i];
    
    if(IsExterior(arr, n))
        cout << "TAK\n";
    else
        cout << (n % 2 == 0 ? "TAK" : "NIE") << "\n";
    
    return 0;
}

bool IsExterior(int *arr, int n) {
    sort(arr, arr + 3);
    return ((arr[0] + 1 == arr[1] && arr[1] + 1 == arr[2]) ||
       (arr[0] == 0 && arr[1] == 1 && arr[2] == n - 1) ||
       (arr[0] == 0 && arr[1] == n - 2 && arr[2] == n - 1));
}
