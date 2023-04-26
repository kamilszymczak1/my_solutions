#include <iostream>

#define MAX_N 100000

using namespace std;

int pairs, quartets;

int amount[MAX_N];
int n;

bool GetResult();

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n;
    
    int val;
    for(int i = 0; i < n; i++) {
        cin >> val;
        amount[val - 1]++;
        if(amount[val - 1] % 2 == 0)
            pairs++;
        if(amount[val - 1] % 4 == 0)
            quartets++;
    }
    
    int q;
    char c;
    cin >> q;
    
    for(int i = 0; i < q; i++) {
        cin >> c >> val;
        val--;
        if(c == '-') {
            if(amount[val] % 2 == 0)
                pairs--;
            if(amount[val] % 4 == 0)
                quartets--;
            amount[val]--;
        } else {
            amount[val]++;
            if(amount[val] % 2 == 0)
                pairs++;
            if(amount[val] % 4 == 0)
                quartets++;
        }
        
        if(GetResult())
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    
    return 0;
}

bool GetResult() {
    if(quartets == 0)
        return false;
    if(pairs >= 4)
        return true;
    return false;
}
