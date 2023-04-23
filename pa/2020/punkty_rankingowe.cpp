#include <iostream>
int a[307], n, result = 1, i, j;
int main() {
    std::ios_base::sync_with_stdio(0);
    for(std::cin >> n, i = 1; i <= n; i++)
        for(j = 0, std::cin >> a[i]; j < i; j++)
            if(a[j] + a[i - j] < a[i])
                result = 0;
    if(result) {
        std::cout << "TAK\n" << n << '\n';
        for(i = 1; i <= n; i++)
            std::cout << a[i] - a[i - 1] << ' ';
        std::cout << '\n';
    } else
        std::cout << "NIE\n";
    return 0;
}
