#include <iostream>
#include <vector>

#define SIZE 10000
#define MAXF 10

using namespace std;

struct Number {
    vector<int>v;
    void Print() {
        if(v.empty())
            cout << '0';
        for(int i = v.size() - 1; i >= 0; i--)
            cout << v[i];
        cout << "\n";
    }
};

int pi[SIZE];
string fib[MAXF];
int mp[MAXF];

int MP(string s1, string s2);
void Generate();

Number ToNumber(int x);
inline Number operator+ (Number &a, Number &b);

int main() {
    ios_base::sync_with_stdio(0);
    
    Generate();
    
    int n;
    string s;
    cin >> s >> n;
    
    if(n <= MAXF) {
        cout << MP(s, fib[n - 1]) << "\n";
    } else {
        Number appear[2];
        for(int i = 0; i < 2; i++)
            appear[i] = ToNumber(MP(s, fib[MAXF - 2 + i]));
        
        Number additional[2];
        for(int i = 0; i < 2; i++)
            additional[i] = ToNumber(MP(s, fib[MAXF - 2 + i] + fib[MAXF - 3 + i]) - MP(s, fib[MAXF - 2 + i]) - MP(s, fib[MAXF - 3 + i]));
        
        for(int i = MAXF; i < n; i++) {
            Number temp = appear[1];
            appear[1] = appear[1] + appear[0];
            appear[1] = appear[1] + additional[i % 2];
            appear[0] = temp;
        }
        
        appear[1].Print();
    }
    
    return 0;
}

void Generate() {
    fib[0] = "b";
    fib[1] = "a";
    for(int i = 2; i < MAXF; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
}

int MP(string s1, string s2) {
    string s = s1 + "#" + s2;
    int x = pi[0] = -1;
    int result = 0;
    for(int i = 1; i <= (int)s.size(); i++) {
        while(x != -1 && s[i - 1] != s[x])
            x = pi[x];
        if((pi[i] = ++x) == s1.size())
            result++;
    }
    return result;
}

Number ToNumber(int x) {
    Number result;
    while(x != 0) {
        result.v.push_back(x % 10);
        x /= 10;
    }
    return result;
}

inline Number operator+ (Number &a, Number &b) {
    Number result;
    int additional = 0;
    for(int i = 0; i < max(a.v.size(), b.v.size()); i++) {
        int sum = additional;
        additional = 0;
        if(i < a.v.size())
            sum += a.v[i];
        if(i < b.v.size())
            sum += b.v[i];
        result.v.push_back(sum % 10);
        additional += sum / 10;
    }
    while(additional != 0) {
        result.v.push_back(additional % 10);
        additional /= 10;
    }
    return result;
}
