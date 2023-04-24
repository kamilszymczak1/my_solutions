#include <iostream>
#include <vector>
using namespace std;
const int MAX_N = 1000007;
bool ticket[MAX_N], bought[MAX_N];
int last[MAX_N];
int m, n, lastTicket = 0;
int main() {
    ios_base::sync_with_stdio(0);
    
    vector<long long>ans;
    cin >> n;
    int a;
    for(int i = 0; i < n; i++) {
        cin >> a;
        ticket[a] = true;
        lastTicket = max(lastTicket, a);
    }
    cin >> m;
    long long currentCustomer = 1;
    for(int i = 0; i < m; i++) {
        cin >> a;
        last[a] += a;
        for(long long i = 0; i < a; i++) {
            while(last[a] <= lastTicket && bought[last[a]])
                last[a] += a;
            if(last[a] > lastTicket)
                break;
            if(ticket[last[a]])
                ans.push_back(currentCustomer + i);
            bought[last[a]] = true;
        }
        currentCustomer += a;
    }
    cout << ans.size() << '\n';
    for(long long x : ans)
        cout << x << '\n';
    
    return 0;
}
