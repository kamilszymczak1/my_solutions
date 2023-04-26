#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

string NumberToString(long long n) {
    string result = "";
    while(n) {
        result += (char)(n % 10 + '0');
        n /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

long long StringToInt(string s) {
    long long result = 0;
    for(char c : s)
        result = result * 10 + c - '0';
    return result;
}

int DiffDigits(int x) {
    vector<bool>used(10, true);
    int result = 0;
    while(x) {
        result += used[x % 10];
        used[x % 10] = false;
        x /= 10;
    }
    return result;
}

void TestCase() {
    int n, k; cin >> n >> k;
    string s = NumberToString(n);
    if(DiffDigits(n) <= k) {
        cout << n << '\n';
        return;
    }
    string result = NumberToString(1ll << 60);
    for(int i = s.size() - 1; i >= 0; i--) {
        set<char>bag;
        for(int j = 0; j < i; j++)
            bag.insert(s[j]);
        if(bag.size() > k || s[i] == '9')
            continue;
        auto it = bag.upper_bound(s[i]);
        if(it == bag.end()) {
            if(bag.size() == k)
                continue;
            bag.insert(s[i] + 1);
        } else if(bag.size() != k) {
            bag.insert(s[i] + 1);
        }
        string newS = s;
        if(bag.size() < k)
            bag.insert('0');
        newS[i] = *bag.upper_bound(s[i]);
        for(int j = i + 1; j < newS.size(); j++)
            newS[j] = *bag.begin();
        if(StringToInt(result) > StringToInt(newS))
            result = newS;
    }
    string bigger(s.size() + 1, '1');
    if(k > 1)
        fill(bigger.begin() + 1, bigger.end(), '0');
    cout << min(StringToInt(result), StringToInt(bigger)) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
