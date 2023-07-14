#include <iostream>
int count[15], n, c;
void f(std::string s) {
    int hash = (s[0] - '1') * 3 + s[1] - 'A';
    if(++count[hash] == (s[0] == '5' ? 2 : 1))
        c++;
}
int main() {
    std::string s;
    std::cin >> n;
    while(n--)
        std::cin >> s, f(s);
    std::cout << (c == 15 ? "TAK" : "NIE") << '\n';
    return 0;
}
