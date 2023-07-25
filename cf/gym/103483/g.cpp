#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
    
using namespace std;
    
long double f(vector<long double>a) {
    return a[0] + a[3] + a[1] * a[2];
}
    
int main() {
    ios_base::sync_with_stdio(0);
    vector<long double>t(4);
    for(auto &x : t)
        cin >> x;
    
    vector<long double>my_t = t;
    
    sort(my_t.begin(), my_t.end());
    
    vector<vector<int>>ind = {
        {1, 2, 3},
        {0, 3, 2},
        {0, 3, 1},
        {1, 2, 0}
    };
    
    vector<long double>best(4, 1);
    
    do {
        
        for(int i = 0; i < 4; i++) {
            
            vector<long double>new_t = my_t;
            if(new_t[ind[i][2]] != 1) {
                new_t[i] = (new_t[ind[i][0]] - 1) * (new_t[ind[i][1]] - 1) / (new_t[ind[i][2]] - 1) + 1;
                
                if(new_t[i] <= my_t[i] && new_t[i] >= 1) {
                    if(f(new_t) > f(best)) {
                        best = new_t;
                    }
                }
                
            }
        }
        
    } while(next_permutation(my_t.begin(), my_t.end()));
    
    vector<int>p = {0, 1, 2, 3};
    do {
        bool ok = true;
        for(int i = 0; i < 4; i++)
            if(best[i] > t[p[i]])
                ok = false;
        if(ok)
            break;
        
    } while(next_permutation(p.begin(), p.end()));
    
    for(int i = 0; i < 4; i++)
        cout << p[i] + 1 << ' ';
    cout << '\n';
    
    
    for(auto d : best)
        cout << fixed << setprecision(10) << d << ' ';
    cout << '\n';
    
    return 0;
}
