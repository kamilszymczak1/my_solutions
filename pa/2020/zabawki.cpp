#include <iostream>
int count[2][2][26], n;
std::string s;
bool Check() {
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 26; j++)
            if(count[0][i][j] != count[1][i][j])
                return false;
    return true;
}
int main() {
    std::cin >> n;
    for(int i = 0; i < 2; i++) {
        std::cin >> s;
        for(int j = 0; j < n; j++)
            count[i][j % 2][s[j] - 'a']++;
    }
    std::cout << (Check() ? "TAK" : "NIE") << '\n';
    return 0;
}
