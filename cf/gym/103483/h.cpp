#include <iostream>
#include <vector>
#include <iomanip>
    
using namespace std;
    
struct Parabola {
    long double a, b, c;
    Parabola(long double _a, long double _b, long double _c) : a(_a), b(_b), c(_c) {}
    long double eval(long double x) {
        return x * x * a + b * x + c;
    }
};
    
long double get_min(long double x, vector<Parabola>&p) {
    long double answer = p[0].eval(x);
    for(auto t : p)
        answer = min(answer, t.eval(x));
    return answer;
}
    
long double get_max(long double x, vector<Parabola>&p) {
    long double answer = p[0].eval(x);
    for(auto t : p)
        answer = max(answer, t.eval(x));
    return answer;
}
    
long double get(long double x, vector<Parabola>&convex, vector<Parabola>&concave) {
    return get_min(x, concave) - get_max(x, convex);
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    vector<Parabola>convex, concave;
    
    int n; cin >> n;
    
    for(int i = 0; i < n; i++) {
        long double a, b, c; cin >> a >> b >> c;
        
        if(a < 0) {
            concave.emplace_back(a, b, c);
        } else {
            convex.emplace_back(a, b, c);
        }
    }
    
    if(convex.empty()) {
        cout << "0 " << get_min(0, concave) - 1 << '\n';
        return 0;
    }
    
    if(concave.empty()) {
        cout << "0 " << get_max(0, convex) + 1 << '\n';
        return 0;
    }
    
    long double lo = -1e9, hi = +1e9;
    
    long double x = 0;
    
    while(hi - lo >= 1e-7) {
        long double l_mid = lo + (hi - lo) / 3;
        long double r_mid = lo + (hi - lo) * 2 / 3;
        
        long double l_value = get(l_mid, convex, concave);
        long double r_value = get(r_mid, convex, concave);
        
        if(l_value > 0) {
            x = l_mid;
            break;
        }
        
        if(r_value > 0) {
            x = r_mid;
            break;
        }
        
        if(l_value < r_value) {
            lo = l_mid;
        } else {
            hi = r_mid;
        }
    }
    
    cout << fixed << setprecision(10) << x << ' ' << (get_max(x, convex) + get_min(x, concave)) / 2 << '\n';
    
    return 0;
}
