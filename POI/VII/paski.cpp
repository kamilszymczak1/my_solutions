#include<bits/stdc++.h>
int a[3], q, res[1007], hi, appear[1007 * 1007], y;
int WhoWins(int x) {
    if(res[x] != -1) return res[x];
    std::fill(appear, appear + hi * 2 + 7, 0);
    for(int i = 0; i < 3; i++) for(int j = 0; j <= x - a[i]; j++) hi = std::max(y = (WhoWins(j) ^ WhoWins(x - j - a[i])), hi), appear[y] = 1;
    return res[x] = (std::find(appear, appear + hi * 2 + 7, false) - appear);
}
int main() {
    std::cin >> a[0] >> a[1] >> a[2] >> q;
    std::fill(res + std::min({a[0], a[1], a[2]}), res + 1007, -1);
    while(std::cin >> q) std::cout << (WhoWins(q) == 0 ? 2 : 1) << "\n";
}
