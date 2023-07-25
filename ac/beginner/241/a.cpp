#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    vector<int>a(10);
    for(int i = 0; i < 10; i++)
        cin >> a[i];
    int k = 0;
    for(int i = 0; i < 3; i++)
        k = a[k];
    cout << k << '\n';
    
    return 0;
}
