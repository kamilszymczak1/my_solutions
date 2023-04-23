#include <bits/stdc++.h>
using namespace std;
    
const long long inf = 1ll << 60;
    
long long test() {
    int n, l; cin >> n >> l;
    l *= 2;
    vector<int>a(n);
    vector<long long>v(n);
    long long answer = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> v[i];
        answer = max(answer, v[i]);
        a[i] *= 2;
    }
        
    vector<vector<long long>>sack(l + 1, vector<long long>(3, -1));
    
    sack[0][0] = 0;
    
    for(int i = 0; i < n; i++) {
        for(int j = 2; j >= 0; j--) {
            
            for(int k = l; k >= 0; k--) {
                if(sack[k][j] != -1) {
                    if(k + a[i] <= l)
                        sack[k + a[i]][j] = max(sack[k + a[i]][j], sack[k][j] + v[i]);
                    if(k + a[i] / 2 <= l && j != 2)
                        sack[k + a[i] / 2][j + 1] = max(sack[k + a[i] / 2][j + 1], sack[k][j] + v[i]);
                }
            }
        }
    }
    
    for(int i = 0; i <= l; i++) {
        for(int j = 0; j < 3; j++) {
            answer = max(answer, sack[i][j]);
        }
    }
    return answer;
}
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i=1; i<=t; ++i) {
        auto wynik = test();
        cout<<"Case #"<<i<<": "<<wynik<<'\n';
    }
}
