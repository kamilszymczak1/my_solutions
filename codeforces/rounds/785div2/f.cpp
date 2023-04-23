#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <cstring>

using namespace std;


const int B = 3;

void Gen(int l, int p, int mirror, vector<vector<int>>&bitGrid, int bit) {
    if(p == B - 3)
        return;
    
    printf("Gen at %d %d, bit = %d\n", l, l + (1 << p), bit);
    
    for(int i = 0; i < (1 << B); i++) {
        for(int j = 0; j < (1 << p); j++) {
            bitGrid[i][j + l] ^= (mirror ^ (j >> (p - 1))) << bit;
        }
    }
    Gen(l, p - 1, 1, bitGrid, bit - 1);
    Gen(l + (1 << (p - 1)), p - 1, 0, bitGrid, bit - 1);
}

void TestCase() {
    vector<vector<int>>bitGrid(1 << B, vector<int>(1 << B, 0));
    for(int bit = 0; bit < B - 1; bit++) {
        for(int i = 0; i < (1 << B); i++) {
            for(int j = 0; j < (1 << B); j++) {
                bitGrid[i][j] ^= ((i >> bit) & 1) << (bit * 2 + 0);
                bitGrid[i][j] ^= ((j >> bit) & 1) << (bit * 2 + 1);
            }
        }
    }
    
    //Gen(0, 5, 0, bitGrid, 8);
    
    for(int bit = 0; bit < B; bit++) {
        printf("bits = %d %d\n", bit * 2, bit * 2 + 1);
        for(int i = 0; i < (1 << B); i++) {
            for(int j = 0; j < (1 << B); j++) {
                printf("%s ", bitset<2>((bitGrid[i][j] >> (bit * 2)) & 3).to_string().c_str());
            }
            printf("\n");
        }
        printf("\n");
    }
    
    int len = 0;
    for(int i = 0; i < (1 << B); i++) {
        for(int j = 1; j < (1 << B); j++) {
            len += bitGrid[i][j - 1] ^ bitGrid[i][j];
            len += bitGrid[j - 1][i] ^ bitGrid[j][i];
        }
    }
    printf("%d\n", len);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
