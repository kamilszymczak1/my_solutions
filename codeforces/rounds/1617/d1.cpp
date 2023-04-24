#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int randint(int a, int b) {
    long long x = (long long)rand() * rand();
    x = (x >> 2) + 3 + rand();
    return a + x % (b - a + 1);
}

void TestCase() {
    int n; cin >> n;
    
    int last = -1, a = 1, b = 2;
    for(int i = 1; i <= n - 2; i++) {
        cout << "? " << i << ' ' << i + 1 << ' ' << i + 2 << '\n' << flush;
        int t; cin >> t;
        if(last != -1 && t != last) {
            a = i - 1, b = i + 2;
            break;
        }
        last = t;
    }
    
    vector<int>impostors, crewmates;
    for(int i = 1; i <= n; i++) {
        if(a == i || b == i)
            continue;
        cout << "? " << a << ' ' << b << ' ' << i << '\n' << flush;
        int t; cin >> t;
        if(t == 0)
            impostors.push_back(i);
        else
            crewmates.push_back(i);
    }
    cout << "? " << crewmates[0] << ' ' << impostors[0] << ' ' << a << '\n' << flush;
    int t; cin >> t;
    if(t == 0)
        impostors.push_back(a);
    else
        impostors.push_back(b);
    
    cout << "! " << impostors.size() << ' ';
    for(int x : impostors)
        cout << x << ' ';
    cout << '\n' << flush;
}

int main() {
    ios_base::sync_with_stdio(0);
    srand(time(NULL));
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
