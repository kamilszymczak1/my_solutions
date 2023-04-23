#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

constexpr int MAX_N = 100007;

char ToDigit(int x) {
    return x + '0';
}

bool Prime(int x) {
    for(int i = 2; i * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;
}

vector<int>GenPrimes(int amount) {
    vector<int>result;
    int i = 10;
    for(int i = 10; result.size() < amount; i++)
        if(Prime(i))
            result.push_back(i);
    return result;
}

void InsertLeftPart(int index, int bound, vector<int>&values, vector<int>&digits, vector<vector<int>>&QPow10, vector<int>&primes, map<vector<int>, vector<int>>&m, const int primesCount) {
    if(index == bound) {
        m[values] = digits;
        return;
    }
    for(int i = 0; i < 10; i++) {
        digits[index] = i;
        for(int j = 0; j < primesCount; j++)
            values[j] = (values[j] + QPow10[j][index] * i) % primes[j];
        InsertLeftPart(index + 1, bound, values, digits, QPow10, primes, m, primesCount);
        for(int j = 0; j < primesCount; j++)
            values[j] = (values[j] - (QPow10[j][index] * i) % primes[j] + primes[j]) % primes[j];
    }
}

string FindRightPart(int index, int bound, vector<int>&values, vector<int>&digits, vector<vector<int>>&QPow10, vector<int>&primes, map<vector<int>, vector<int>>&m, const int primesCount) {
    if(index == bound) {
        if(m[values].size() != 0) {
            string result = "";
            for(int i = 0; i < digits.size() / 2; i++)
                result += ToDigit(m[values][i]);
            for(int i = digits.size() / 2; i < digits.size(); i++)
                result += ToDigit(digits[i]);
            reverse(result.begin(), result.end());
            return result;
        }
        
        return "";
    }
    
    for(int i = 0; i < 10; i++) {
        digits[index] = i;
        for(int j = 0; j < primesCount; j++)
            values[j] = (values[j] - (QPow10[j][index] * i) % primes[j] + primes[j]) % primes[j];
        string result = FindRightPart(index + 1, bound, values, digits, QPow10, primes, m, primesCount);
        if(result != "")
            return result;
        for(int j = 0; j < primesCount; j++)
            values[j] = (values[j] + QPow10[j][index] * i) % primes[j];
    }
    return "";
}


string TestCase(vector<int>digits) {
    string s; cin >> s;
    int n = lower_bound(digits.begin(), digits.end(), s.size()) - digits.begin();
    const int primesCount = 20;
    vector<int>primes = GenPrimes(primesCount), k(primesCount, 0), pow10(primesCount, 1), factorial(primesCount, 1);
    
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < primesCount; j++)
            factorial[j] = (factorial[j] * i) % primes[j];
            
    vector<vector<int>>QPow10(primesCount);
    //Qpow10[i][j] -> 10 ^ position of jth query modulo ith primeNumber
    int queryCount = 0;
    for(int i = s.size() - 1; i >= 0; i--) {
        if(s[i] == '?') {
            for(int j = 0; j < primesCount; j++)
                QPow10[j].push_back(pow10[j]);
            queryCount++;
        }
            
        for(int j = 0; j < primesCount; j++)
            pow10[j] = (pow10[j] * 10) % primes[j];
        
    }
    
    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j < primesCount; j++)
            k[j] = (k[j] * 10 + (s[i] == '?' ? 0 : (s[i] - '0'))) % primes[j];
    }
    
    string result = "";
    if(queryCount == 1) {
        for(int number = 0; number < 10; number++) {
            bool valid = true;
            for(int i = 0; i < primesCount; i++) {
                int L = (QPow10[i][0] * number) % primes[i];
                int R = (factorial[i] - k[i] + primes[i]) % primes[i];
                if(L != R)
                    valid = false;
            }
            if(valid) {
                result += ToDigit(number);
                return result;
            }
        }
    }
    
    map<vector<int>, vector<int>>m;
    vector<int>resDigits(queryCount, 0), valuesLeft(primesCount, 0), valuesRight(primesCount, 0);
    InsertLeftPart(0, queryCount / 2, valuesLeft, resDigits, QPow10, primes, m, primesCount);
    for(int i = 0; i < primesCount; i++)
        valuesRight[i] = (factorial[i] - k[i] + primes[i]) % primes[i];
    return FindRightPart(queryCount / 2, queryCount, valuesRight, resDigits, QPow10, primes, m, primesCount);
}

int main() {
    ios_base::sync_with_stdio(0);
    vector<int>factorialDigits(MAX_N, 0);
    factorialDigits[0] = 1;
    long double logSum = 0;
    for(int i = 1; i < MAX_N; i++) {
        logSum += log10(i);
        factorialDigits[i] = floor(logSum + 1);
    }
    int t; cin >> t;
    while(t--)
        cout << TestCase(factorialDigits) << '\n';
    return 0;
}
