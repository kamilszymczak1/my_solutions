#include <iostream>
#include <vector>
#include <map>

#define MAX_A 32001
#define inf 11

using namespace std;

vector<long long>sums[9];
map<long long, bool>m;

void Generate(int level);

int minLength[MAX_A];

int main() {
    ios_base::sync_with_stdio(0);
    
    int base, n, val;
    cin >> base >> n;
    
    val = 0;
    int power = 1;
    
    for(int i = 1; i < 9; i++) {
        val += base * power;
        power = power * 10;
        sums[i].push_back(val);
    }
    
    Generate(2);
    
    fill(minLength, minLength + MAX_A, inf);
    
    for(int i = 1; i < 10; i++) {
        for(long long x : sums[i]) {
            if(x > 0 && x < MAX_A)
                minLength[x] = min(i, minLength[x]);
        }
    }
    
    
    while(n--) {
        cin >> val;
        if(minLength[val] == inf)
            cout << "NIE\n";
        else
            cout << minLength[val] << "\n";
    }
}

void Generate(int level) {
    if(level >= 10)
        return;
    
    for(int i = 1; i <= level / 2; i++) {
        int j = i;
        int k = level - i;
        
        for(long long x : sums[j]) {
            for(long long y : sums[k]) {
                vector<long long>v = {x + y, x - y, y - x, x * y};
                
                if(y != 0 && abs(x) % abs(y) == 0)
                    v.push_back(x / y);
                if(x != 0 &&  abs(y) % abs(x) == 0)
                    v.push_back(y / x);
                
                for(long long x : v) {
                    if(m[x] == 0) {
                        sums[level].push_back(x);
                        m[x] = 1;
                    }
                }
            }
        }
    }
    
    Generate(level + 1);
}
