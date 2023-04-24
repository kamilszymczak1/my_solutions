#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct Number {
    ll val;
    int divisors;
    Number(ll v, int d) {
        val = v;
        divisors = d;
    }
    Number() {}
    inline bool operator() (const Number &a, const Number &b) {
        return a.val < b.val;
    }
};

const int primesCount = 9;
ll primes[primesCount];

vector<Number>candidates;

void GeneratePrimes();
bool Prime(int x);

void Generate(int layer, int maxIndex, ll number, int divisors, ll hi);

int main() {
    ios_base::sync_with_stdio(0);
    
    GeneratePrimes();
    
    ll n;
    cin >> n;
    
    Generate(0, 31, 1, 1, n);
    
    sort(candidates.begin(), candidates.end(), Number());
    
    vector<int>antiprimes;
    
    int maxDivisors = 0;
    
    for(Number number : candidates)
        if(number.divisors > maxDivisors)
            maxDivisors = number.divisors, antiprimes.push_back(number.val);
        
    cout << antiprimes.back() << "\n";
    
    return 0;
}

void Generate(int layer, int maxIndex, ll number, int divisors, ll hi) {
    candidates.push_back(Number(number, divisors));
    
    if(layer >= primesCount)
        return;
    
    for(int i = 1; i <= maxIndex; i++) {
        if(number * primes[layer] <= hi) {
            number = number * primes[layer];
            Generate(layer + 1, maxIndex, number, divisors * (i + 1), hi);
        }
    }
}

void GeneratePrimes() {
    int j = 2;
    for(int i = 0; i < primesCount; i++) {
        while(!Prime(j))
            j++;
        primes[i] = j++;
    }
}

bool Prime(int x) {
    for(int i = 2; i * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;
}
