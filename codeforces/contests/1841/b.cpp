#include <iostream>
#include <vector>

using namespace std;

void test_case() {
    int q; cin >> q;
    vector<int>v, ans;
    for(int i = 0; i < min(q, 2); i++) {
        int x; cin >> x;
        v.push_back(x);
        ans.push_back(1);
    }
    
    int inv_count = v[0] == v[1] ? 0 : 1;
    
    for(int i = 2; i < q; i++) {
        int x; cin >> x;
        
        int new_inv_count = inv_count;
        new_inv_count -= v[0] < v.back();
        new_inv_count += x < v.back();
        new_inv_count += x > v[0];
        
        if(new_inv_count <= 1) {
            inv_count = new_inv_count;
            v.push_back(x);
            ans.push_back(1);
        } else {
            ans.push_back(0);
        }
    }
    for(int x : ans)
        cout << x;
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
