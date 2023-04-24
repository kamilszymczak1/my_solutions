//Kamil Szymczak
#include "zerlib.h"
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL));
    int n = daj_n();
    vector<int>res(n, -1);
    if(n == 3) {
        int a = suma(0, 1), b = suma(1, 2), c = suma(0, 2);
        res[0] = (a + c - b) / 2;
        res[1] = (a + b - c) / 2;
        res[2] = (b + c - a) / 2;
        odpowiedz(res);
        return 0;
    }
    vector<int>order(n);
    for(int i = 0; i < n; i++)
        order[i] = i;
    for(int i = 0; i < n; i++)
        swap(order[i], order[rand() % n]);
    
    
    vector<int>wrong;
    for(int i = 0; i < n / 2; i++) {
        int a = order[i * 2], b = order[i * 2 + 1];
        int x = suma(a, b);
        if(x == 1) {
            wrong.push_back(i);
        } else {
            res[a] = res[b] = x / 2;
        }
    }
    
    while(wrong.size() >= 2) {
        int i = wrong.back(); wrong.pop_back();
        int j = wrong.back(); wrong.pop_back();
        int a = order[i * 2], b = order[i * 2 + 1];
        int c = order[j * 2], d = order[j * 2 + 1];
        int x = suma(a, c);
        if(x == 1) {
            x = suma(b, c);
            res[a] = res[d] = (2 - x) / 2;
            res[b] = res[c] = x / 2;
        } else {
            res[a] = res[c] = x / 2;
            res[b] = res[d] = (2 - x) / 2;
        }
    }
    
    int pos[2] = {-1, -1};
    for(int i = 0; i < n; i++) {
        if(res[i] != -1) {
            pos[res[i]] = i;
        }
    }
    
    if(wrong.size() == 1) {
        int i = wrong.back();
        if(pos[0] != -1) {
            int x = suma(pos[0], order[i * 2]);
            if(x == 0) {
                res[order[i * 2]] = 0;
                res[order[i * 2 + 1]] = 1;
            } else {
                res[order[i * 2]] = 1;
                res[order[i * 2 + 1]] = 0;
            }
        } else {
            int x = suma(pos[1], order[i * 2]);
            if(x == 2) {
                res[order[i * 2]] = 1;
                res[order[i * 2 + 1]] = 0;
            } else {
                res[order[i * 2]] = 0;
                res[order[i * 2 + 1]] = 1;
            }
        }
    }
    
    if(n % 2 != 0) {
        res[order[n - 1]] = suma(order[n - 1], order[0]) - res[order[0]];
    }
    
    odpowiedz(res);
    
    return 0;
}
