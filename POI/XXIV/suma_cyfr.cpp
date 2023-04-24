#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long inf = 1e18 + 7;
const int MAX_N = 207;

long long cnt[MAX_N][MAX_N][MAX_N];
long long pow10ModM[MAX_N];

void Calc(int s, int m) {
    cnt[0][0][0] = 1;
    pow10ModM[1] = 1;
    for(int digit = 0; digit <= min(s, 9); digit++)
        cnt[1][digit][digit % m] += 1;
    for(int i = 2; i < MAX_N; i++) {
        pow10ModM[i] = (pow10ModM[i - 1] * 10) % m;
        for(int prevSum = 0; prevSum <= s; prevSum++) {
            for(int prevMod = 0; prevMod < m; prevMod++) {
                for(int newDigit = 0; newDigit <= min(s - prevSum, 9); newDigit++) {
                    long long newSum = prevSum + newDigit;
                    long long newMod = (prevMod + pow10ModM[i] * newDigit) % m;
                    cnt[i][newSum][newMod] = min(cnt[i][newSum][newMod] + cnt[i - 1][prevSum][prevMod], inf);
                }
            }
        }
    }
}

string Query(long long k, int s, int m) {
    vector<int>digits;
    int requiredSum = s, requiredMod = 0;
    for(int i = MAX_N - 1; i >= 1; i--) {
        int digit = 0;
        while(digit <= min(requiredSum, 9) && k >= cnt[i - 1][requiredSum - digit][(requiredMod - (digit * pow10ModM[i]) % m + m) % m]) {
            k -= cnt[i - 1][requiredSum - digit][(requiredMod - (digit * pow10ModM[i]) % m + m) % m];
            digit++;
        }
        if(digit == 10 || digit > requiredSum) {
            return "NIE";
        }
            
        requiredSum -= digit;
        requiredMod = (requiredMod - (digit * pow10ModM[i]) % m + m) % m;
        digits.push_back(digit);
    }
    if(k > 0)
        return "NIE";
    reverse(digits.begin(), digits.end());
    while(digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
    if(digits.size() > 200)
        return "NIE";
    string result = "";
    while(!digits.empty()) {
        result = result + (char)(digits.back() + '0');
        digits.pop_back();
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int s, m, q; cin >> s >> m >> q;
    Calc(s, m);
    
    while(q--) {
        long long k; cin >> k;
        cout << Query(k - 1, s, m) << '\n';
    }
    
    return 0;
}
