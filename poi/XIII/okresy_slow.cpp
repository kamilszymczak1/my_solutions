#include <iostream>

const int MAX_N = 1000007;

std::string s;
int PI[MAX_N], shortest[MAX_N], n;

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin >> n >> s;
    long long result = 0;
    int k = PI[0] = shortest[0] = -1;
    for(int i = 1; i <= n; i++) {
        while(k >= 0 && s[i - 1] != s[k])
            k = PI[k];
        PI[i] = ++k;
        shortest[i] = shortest[PI[i]] > 0 ? shortest[PI[i]] : PI[i];
        result += shortest[i] == 0 ? 0 : i - shortest[i];
    }   
    std::cout << result << "\n";
    
    return 0;
}
