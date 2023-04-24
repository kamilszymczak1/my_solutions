#include <iostream>
#include <vector>

#define MAX_B 1000000

#define inf 10000000000000

using namespace std;

typedef long long ll;

int a[MAX_B];
ll b;

vector<ll>amount(0);
vector<int>number(0);

int Query(ll val);

int main() {
    ios_base::sync_with_stdio(0);
    
    int k;
    ll val, sum = 0;
    cin >> b >> k;
    
    for(ll i = 0; i < b; i++) {
        cin >> a[i];
        sum += (i * a[i]);
    }
    
    ll r = sum % (b - 1);
    if(r != 0)
        a[r]--;
    
    amount.push_back(a[0] - 1);
    number.push_back(0);
    
    for(int i = 1; i < b; i++) {
        if(a[i] != 0) {
            ll b = amount[amount.size() - 1];
            amount.push_back(b + (ll)a[i]);
            number.push_back(i);
        }
    }
    
    for(int i = 0; i < k; i++) {
        cin >> val;
        cout << Query(val) << "\n";
    }
    
    return 0;
}

int Query(ll val) {
    if(val > amount.back())
        return -1;
    
    int beg = 0, end = amount.size() - 1;
    
    while(beg <= end) {
        int mid = (beg + end) / 2;
        if(amount[mid] < val)
            beg = mid + 1;
        else
            end = mid - 1;
    }
    return number[beg];
}
