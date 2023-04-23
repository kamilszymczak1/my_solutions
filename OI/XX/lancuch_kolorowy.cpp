#include <iostream>
#include <vector>

#define MAX_N 1000001

using namespace std;

int color[MAX_N];
int colorCount[MAX_N];
int need[MAX_N];
int arr[MAX_N];
int n, m;
long long amount;

void Load();

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    Load();
    
    if(amount > n) {
        cout << "0\n";
        return 0;
    }

    for(int i = 0; i < amount; i++)
        colorCount[color[i]] = colorCount[color[i]] + 1;
    
    int matchCount = 0;
    
    for(int i = 1; i <= n; i++)
        if(colorCount[i] == need[i])
            matchCount = matchCount + 1;
    
    int result = 0;
    
    int dif;
    
    for(int i = 0; i + amount < n; i++) {
        if(matchCount == n)
            result = result + 1;
        
        dif = colorCount[color[i]] - need[color[i]];
        if(dif == 0)
            matchCount = matchCount - 1;
        colorCount[color[i]] = colorCount[color[i]] - 1;
        
        if(dif == 1)
            matchCount = matchCount + 1;
        
        dif = colorCount[color[i + amount]] - need[color[i + amount]];
        if(dif == 0)
            matchCount = matchCount - 1;
        colorCount[color[i + amount]] = colorCount[color[i + amount]] + 1;
        
        if(dif == -1)
            matchCount = matchCount + 1;
    }
    
    if(matchCount == n)
        result++;
    
    cout << result << "\n";
    
    return 0;
}

void Load() {
    int val;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> arr[i];
        amount = amount + arr[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> val;
        need[val] = arr[i];
    }
    for(int i = 0; i < n; i++)
        cin >> color[i];
}
