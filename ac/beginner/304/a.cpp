#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    
    vector<string>name(n);
    vector<int>age(n);
    
    for(int i = 0; i < n; i++)
        cin >> name[i] >> age[i];
    
    int k = min_element(age.begin(), age.end()) - age.begin();
    
    for(int i = 0; i < n; i++) {
        cout << name[(k + i) % n] << '\n';
    }
}
