#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int TestCase() {
    int n; cin >> n;
    string s; cin >> s;
    multiset<int, greater<int>>twoSides, oneSide;
    int firstOneIndex = find(s.begin(), s.end(), '1') - s.begin();
    int lastOneIndex = s.rend() - find(s.rbegin(), s.rend(), '1') - 1;
    if(firstOneIndex == n)
        return 0;
    oneSide.insert(firstOneIndex);
    oneSide.insert(n - lastOneIndex - 1);
    
    for(int i = firstOneIndex; i < lastOneIndex; i++) {
        if(s[i] == '0') {
            int j = i;
            while(s[j] == '0')
                j++;
            twoSides.insert(j - i);
            i = j;
        }
    }
        
    
    
    
    int days = 0, result = 0;
    while(!oneSide.empty() || !twoSides.empty()) {
        while(!oneSide.empty() && *oneSide.begin() - days <= 0)
            oneSide.erase(oneSide.begin());
        while(!twoSides.empty() && *twoSides.begin() - 2 * days <= 0)
            twoSides.erase(twoSides.begin());
        
        if(!oneSide.empty() && !twoSides.empty()) {
            int one = *oneSide.begin() - days, two = *twoSides.begin() - 2 * days;
            if(two < one * 2) {
                result += one;
                oneSide.erase(oneSide.begin());
            } else {
                twoSides.erase(twoSides.begin());
                result++;
                oneSide.insert(two - 1 + days);
            }
        } else if(!oneSide.empty()) {
            int one = *oneSide.begin() - days;
            result += one;
            oneSide.erase(oneSide.begin());
        } else if(!twoSides.empty()) {
            int two = *twoSides.begin() - 2 * days;
            twoSides.erase(twoSides.begin());
            result++;
            oneSide.insert(two - 1 + days);
        }
        days++;
    }
    
    return n - result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        cout << TestCase() << '\n';
    
    return 0;
}
