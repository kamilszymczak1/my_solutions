#include <iostream>
#include <vector>
#include <set>
#include <bitset>

using namespace std;

const int MAX_A = 2'500'007;
const long long mod = 1'000'000'007;

bitset<MAX_A>bag;
int n, count[MAX_A], bag_size, A = 0;

void bag_insert(int x) {
    bag = bag | (bag << x);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    
    int mx = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        count[x]++;
        A += x;
        mx = max(mx, x);
    }
    
    bag_size = A / 2 + 1;
    
    bag[0] = true;
    
    count[mx]--;
    
    for(int i = 1; i <= mx; i++) {
        int b = 1;
        while(b <= count[i]) {
            bag_insert(i * b);
            count[i] -= b;
            b *= 2;
        }
        if(count[i] > 0)
            bag_insert(count[i] * i);
    }
    
    int answer = 0;
    int my_A = A - mx;
    
    for(int i = 0; i <= bag_size; i++) {
        
        if(bag[i]) {
            
            if(i <= my_A - i && i + mx >= my_A - i) {
                answer = max(answer, i + mx);
            }
        }
    }
    
    cout << answer << '\n';
    
    
    return 0;
}
