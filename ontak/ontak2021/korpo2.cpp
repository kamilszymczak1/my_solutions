#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

vector<long double> DFS(int x, int games, string &decision) {
    if(games == 0)
        return {0};
    const int subtreeGames = (games - 1) / 2;
    vector<long double>l = DFS(x * 2 + 1, subtreeGames, decision);
    vector<long double>r = DFS(x * 2 + 2, subtreeGames, decision);
    
    if(decision[x * 2 + 1] != decision[x]) {
        for(long double &val : l)
            val = 1 - val;
    }
    if(decision[x * 2 + 2] != decision[x]) {
        for(long double &val : r)
            val = 1 - val;
    }
    
    long double coefficient1 = 1; //(subtreeGames!^2) / (games!)
    for(int i = 1; i <= subtreeGames; i++) {
        coefficient1 *= i / (long double)(i + subtreeGames);
    }
    coefficient1 /= games;
    
    vector<long double>result(games + 1, 0);
    for(int x = 0; x <= subtreeGames; x++) {
        vector<long double>coefficient2(subtreeGames + 1, 0), coefficient3(subtreeGames + 1, 0);
        //2 -> (x + y over y), 3 -> (games - x - y - 1 over subtreeGames - y)
        coefficient2[0] = coefficient3[subtreeGames] = 1;
        for(int i = 1; i <= subtreeGames; i++) {
            coefficient2[i] = coefficient2[i - 1] / i * (x + i);
            coefficient3[subtreeGames - i] = coefficient3[subtreeGames - i + 1] / i * (games - x - subtreeGames + i - 1);
        }
            
        for(int y = 0; y <= subtreeGames; y++) {
            result[x + y + 1] += l[x] * r[y] * coefficient1 * coefficient2[y] * coefficient3[y];
        }
    }
    for(int i = 1; i <= games; i++)
        result[i] += result[i - 1];
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    string decision; cin >> decision;
    
    long double result = DFS(0, (1 << (n - 1)) - 1, decision).back();
    
    if(decision[0] == 'A')
        result = 1 - result;
    
    cout << fixed << setprecision(10) << result << '\n';
    
    return 0;
}

/*
3
AABBBBA
*/
