#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void FindSum(int x);
bool Prime(int x);

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, val;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> val;
        FindSum(val);
    }
    
    return 0;
}

void FindSum(int x) {
    if(Prime(x)) {
        cout << 1 << "\n" << x << "\n";
        return;
    }
    
    vector<int>result;
    
    if(x % 2 != 0) {
        x -= 3;
        result.push_back(3);
    }

    int i = 5;
    
    if(x < 20)
        i -= 2;
    int j = x;
    while(i + j != x) {
        if(i + j > x)
            do
                j--;
            while(!Prime(j));
        else
            do
                i++;
            while(!Prime(i));
    }
    
    result.push_back(i);
    result.push_back(j);
    sort(result.begin(), result.end());
                
    
    cout << result.size() << "\n";
    for(int x : result)
        cout << x << " ";
    cout << "\n";
}

bool Prime(int x) {
    for(int i = 2; i * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;
}
