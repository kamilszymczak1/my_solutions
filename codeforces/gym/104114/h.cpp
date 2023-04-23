#include <iostream>
#include <vector>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>first(n), second, third;
    
    for(int i = 0; i < n; i++)
        cin >> first[i];
    
    vector<pair<int, int>>moves;
    while(first.size() != 0) {
        second.push_back(first.back());
        first.pop_back();
        moves.emplace_back(1, 2);
        while(!third.empty() && third.back() < second.back()) {
            first.push_back(third.back());
            third.pop_back();
            moves.emplace_back(3, 1);
        }
        third.push_back(second.back());
        second.pop_back();
        moves.emplace_back(2, 3);
        while(!first.empty() && first.back() < third.back()) {
            third.push_back(first.back());
            first.pop_back();
            moves.emplace_back(1, 3);
        }
    }
    
    cout << moves.size() << '\n';
    for(auto [a, b] : moves)
        cout << a << ' ' << b << '\n';
    cout << '\n';
    return 0;
}
