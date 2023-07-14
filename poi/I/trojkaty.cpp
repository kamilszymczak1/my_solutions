#include <algorithm>
#include <iostream>

using namespace std;

struct Fraction {
    int p, q;
    Fraction(int _p, int _q) : p(_p), q(_q) {}
    Fraction(string &s) {
        int slashInd = find(s.begin(), s.end(), '/') - s.begin();
        p = q = 0;
        for(int i = 0; i < slashInd; i++)
            p = p * 10 + s[i] - '0';
        for(int i = slashInd + 1; i < s.size(); i++)
            q = q * 10 + s[i] - '0';
    }
};

bool operator<= (Fraction a, Fraction b) {
    return a.p * b.q <= b.p * a.q;
}

bool operator> (Fraction a, Fraction b) {
    return a.p * b.q > b.p * a.q;
}

Fraction operator+(Fraction &a, Fraction &b) {
    return Fraction(a.p * b.q + b.p * a.q, a.q * b.q);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    Fraction hi(0, 1), lo1(10000, 1), lo2(10000, 1);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        Fraction x(s);
        if(x <= lo1) {
            lo2 = lo1;
            lo1 = x;
        } else if(x <= lo2) {
            lo2 = x;
        }
        if(x > hi)
            hi = x;
    }
    cout << (lo1 + lo2 > hi ? "TAK" : "NIE") << '\n';
}
// 
