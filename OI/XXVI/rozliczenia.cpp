#include <iostream>
#include <vector>
#define lsb(x) ((x) & (-x))
using namespace std;
int M, current, count;
long long a[1000001];

long long PrefixSum(int i) {
    long long result = 0;
    for(i++; i > 0; i -= lsb(i))
        result += a[i];
    return result;
}

long long Sum(int a, int b) {
    return PrefixSum(b) - PrefixSum(a - 1);
}

void Add(int i, long long value) {
    for(i++; i <= M; i += lsb(i))
        a[i] += value;
}

void Insert(int i, long long value) {
    Add(i, value - Sum(i, i));
}

void inicjuj(int m) {
    M = m;
    current = -1;
}

void dodaj(int k) {
    current = current + 1;
    if(current >= M)
        current = current - M;
    Insert(current, k);
    count++;
}

void koryguj(int i, int k) {
    i--;
    if(current - i < 0)
        i -= M;
    Add(current - i, k);
}

long long suma(int i) {
    i = min(i, count);
    i--;
    long long result = Sum(max(0, current - i), current);
    if(current - i < 0)
        result += Sum(current - i + M, M - 1);
    return result;
}
