#include <iostream>

using namespace std;

int take();

int GetMax(int p1, int p2, int a1, int a2, int w1, int w2);

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, p1, p2, a1, a2, w1, w2;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> p1 >> p2 >> a1 >> a2 >> w1 >> w2;
        if(w1 > w2)
            swap(w1, w2), swap(a1, a2);
        int result1 = GetMax(p1, p2, a1, a2, w1, w2);
        int result2 = GetMax(p2, p1, a1, a2, w1, w2);
        cout << max(result1, result2) << "\n";
    }
    
    return 0;
}

int GetMax(int p1, int p2, int a1, int a2, int w1, int w2) {
    int amount1 = min(a1, p1 / w1);
    a1 -= amount1;
    int amount2 = min(a1, p2 / w1);
    a1 -= amount2;
    
    int result = amount1 + amount2;
    
    while(amount2 * w1 <= p2) {
        int amount21 = (p1 - amount1 * w1) / w2;
        int amount22 = (p2 - amount2 * w1) / w2;
        result = max(result, amount1 + amount2 + min(amount21 + amount22, a2));
        amount2++;
        amount1--;
        if(amount1 < 0)
            return result;
    }
    
    return result;
}
