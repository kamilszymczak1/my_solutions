#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

bool Prime(long long x) {
    for(long long i = 2; i * i <= x; i++)
        if(x % i == 0)
            return false;
    return true;
}

long long RandPrime(long long start, long long end) {
    long long result;
    for(result = rand() % (end - start + 1) + start; !Prime(result); result++) {}
    return result;
}

void InsertLeftQueries(int index, int bound, long long value, vector<long long>&QPow10, string current, map<long long, string>&m, long long mod) {
    if(index == bound)
        m[value] = current;
        return;
    for(int i = 0; i < 10; i++)
        InsertLeftQueries(index + 1, bound, (value + QPow10[index] * i) % mod, QPow10, current + (char)(i + '0'), m, mod);
}

string FindRightQueries(int index, long long value, vector<long long>&QPow10, string current, map<long long, string>&m, long long mod) {
    if(index == QPow10.size())
        return m[value].size() > 0 ? m[value] + current : "";
    for(int i = 0; i < 10; i++) {
        string result = FindRightQueries(index + 1, (value - (QPow10[index] * i) % mod + mod) % mod, QPow10, current + (char)(i + '0'), m, mod);
        if(result != "")
            return result;
    }
    return "";
}

string TestCase(vector<int>&factorialDigits) {
    string s; cin >> s;
    int n = lower_bound(factorialDigits.begin(), factorialDigits.end(), s.size()) - factorialDigits.begin();
    vector<long long>QPow10;
    long long pow10 = 1, k = 0, factorial = 1, mod = RandPrime(1.5e12, 1.7e12);
    int queryCount = 0;
    for(long long i = 2; i <= n; i++)
        factorial = (factorial * i) % mod;
    for(int i = s.size() - 1; i >= 0; i--) {
        if(s[i] == '?') {
            QPow10.push_back(pow10);
            queryCount++;
        } else {
            k = (k + (s[i] - '0') * pow10) % mod;
        }
        pow10 = (pow10 * 10) % mod;
    }
    reverse(QPow10.begin(), QPow10.end());
    map<long long, string>m;
    const int leftQueries = max(1, queryCount / 2);
    InsertLeftQueries(0, leftQueries, 0, QPow10, "", m, mod);
    return FindRightQueries(leftQueries, (factorial - k + mod) % mod, QPow10, "", m, mod);
}

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    const int MAX_N = 100007;
    vector<int>factorialDigits(MAX_N, 0);
    long double currentLog = 0;
    factorialDigits[0] = 1;
    for(int i = 1; i < MAX_N; i++) {
        currentLog += log10(i);
        factorialDigits[i] = floor(currentLog + 1);
    }
    
    int t; cin >> t;
    while(t--)
        cout << TestCase(factorialDigits) << '\n';
    
    return 0;
}
