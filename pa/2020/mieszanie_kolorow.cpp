#include <iostream>
int arr[3][1000007], n, m, l, r, k, result = 0;
int main() {
    std::ios_base::sync_with_stdio(0);
    for(std::cin >> n >> m; m--;)
        std::cin >> l >> r >> k, arr[k - 1][l - 1]++, arr[k - 1][r]--;
    for(int i = 0; i < 3; i++)
        for(int j = 1; j < n; j++)
            arr[i][j] += arr[i][j - 1];
    for(int i = 0; i < n; i++)
        result += (arr[0][i] > 0 && arr[1][i] > 0 && arr[2][i] == 0);
    std::cout << result << '\n';
    return 0;
}
