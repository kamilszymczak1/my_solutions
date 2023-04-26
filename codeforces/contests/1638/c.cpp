#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>components;
    for(int i = 0; i < n; i++) { 
        int x; cin >> x;
        int highest = x;
        while(!components.empty() && components.back() > x) {
            highest = max(highest, components.back());
            components.pop_back();
        }
        components.push_back(highest);
    }
    cout << components.size() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
