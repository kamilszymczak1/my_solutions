#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const __int128_t inf = 1'000'000'000'000'000'000;

struct Fraction {
    __int128_t a, b;
    Fraction(__int128_t x) : a(x), b(1) {}
    Fraction(__int128_t x, __int128_t y) : a(x), b(y) {}
    Fraction() : a(0), b(1) {}
};

bool operator== (Fraction x, Fraction y) { return x.a * y.b == x.b * y.a; }
bool operator<  (Fraction x, Fraction y) { 
    if(x.b * y.b < 0)
        return x.a * y.b > x.b * y.a;
    return x.a * y.b < x.b * y.a; 
}
bool operator<= (Fraction x, Fraction y) { return x == y || x < y; }
bool operator>  (Fraction x, Fraction y) { 
    if(x.b * y.b < 0)
        return x.a * y.b < x.b * y.a;
    return x.a * y.b > x.b * y.a; 
}
bool operator>= (Fraction x, Fraction y) { return x == y || x > y; }

Fraction operator+(Fraction x, Fraction y) { return Fraction(x.a * y.b + y.a * x.b, x.b * y.b); }
Fraction operator-(Fraction x, Fraction y) { return Fraction(x.a * y.b - y.a * x.b, x.b * y.b); }
Fraction operator*(Fraction x, Fraction y) { return Fraction(x.a * y.a, x.b * y.b); }
Fraction operator/(Fraction x, Fraction y) { return Fraction(x.a * y.b, x.b * y.a); }
Fraction operator-(Fraction x) { return Fraction(-x.a, x.b); }

Fraction meet_point(pair<Fraction, Fraction>a, pair<Fraction, Fraction>b, Fraction shift) {
    a.second = a.second + shift;
    b.second = b.second + shift;
    if(a.first == b.first)
        return Fraction(inf);
    return (a.second - b.second) / (b.first - a.first);
}

bool remove_check(vector<pair<Fraction, Fraction>>&segments, Fraction velocity, Fraction x, Fraction shift) {
    int s = segments.size();
    if(s > 0 && velocity <= segments.back().first)
        return true;
    if(s < 2)
        return false;
    Fraction meet_point_1 = meet_point(segments[s - 1], make_pair(velocity, x), shift);
    Fraction meet_point_2 = meet_point(segments[s - 1], segments[s - 2], shift);
    return meet_point_2 <= meet_point_1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, D, W, M; cin >> n >> D >> W >> M;
    
    Fraction my_velocity(W, M), my_d(D);
    
    vector<Fraction>velocity(n), x(n), d(n);
    for(int i = 0; i < n; i++) {
        int _x, _d; cin >> _x >> _d;
        x[i] = Fraction(_x);
        d[i] = Fraction(_d);
        int w, m; cin >> w >> m;
        velocity[i] = Fraction(w, m);
    }
    
    vector<pair<Fraction, Fraction>>segments;
    
    int result = 1;
    
    Fraction shift(0);
    
    for(int i = n - 1; i > 0; i--) {
        
        while(remove_check(segments, velocity[i], x[i] - shift, shift))
            segments.pop_back();
        segments.emplace_back(velocity[i], x[i] - shift);
        shift = shift - d[i];
        
        int s = segments.size();
        
        int lo = 0, hi = s - 1;
        while(lo < hi) {
            const int mid = (lo + hi) / 2;
            
            Fraction l = mid == s - 1 ? Fraction(-inf) : meet_point(segments[mid + 1], segments[mid], shift);
            
            Fraction my_meet = meet_point(make_pair(my_velocity, -shift), segments[mid], shift);
            
            if(my_meet >= l)
                hi = mid;
            else
                lo = mid + 1;
        }
        
        {
            Fraction my_meet = meet_point(make_pair(my_velocity, -shift), segments[lo], shift);
            if(my_velocity * my_meet >= velocity[i - 1] * my_meet + my_d + x[i - 1]) {
                result++;
            }
        }
        
    }
    
    cout << result << '\n';
    
    return 0;
}
