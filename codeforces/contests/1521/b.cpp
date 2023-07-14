#include <set>
#include <iostream>

using namespace std;

const int MAX_N = 100007;
int v[MAX_N];

void TestCase() {
    int n; cin >> n;
    int smallest = 0;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        if(v[i] < v[smallest])
            smallest = i;
    }
    cout << n - 1 << '\n';
    if(smallest == 0) {
        for(int i = 1; i < n; i++) {
            cout << 1 << ' ' << i + 1 << ' ' << v[0] << ' ' << v[0] + (i & 1) << '\n';
        }
    } else {
        for(int i = smallest + 1; i < n; i++) {
            cout << smallest + 1 << ' ' << i + 1 << ' ' << v[smallest] << ' ' << v[smallest] + ((i - smallest) & 1) << '\n';
        }
        for(int i = smallest - 1; i >= 0; i--) {
            cout << smallest + 1 << ' ' << i + 1 << ' ' << v[smallest] << ' ' << v[smallest] + ((smallest - i) & 1) << '\n';
        }
    }
}

int main() {
    int t;
    cin >> t;
    while(t--)
        TestCase();
    
    
    return 0;
}
