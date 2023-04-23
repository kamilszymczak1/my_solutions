#include <iostream>

using namespace std;

bool appear[20000];
bool number[100];

int FindNumber(int remainder, int index, int mod);
int GetVal(int layer);

int main() {
    ios_base::sync_with_stdio(0);
    int n, value, result;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> value;
        fill(appear, appear + value, false);
        result = FindNumber(0, 0, value);
        if(result <= 0)
            cout << "BRAK\n";
        else {
            for(int i = 0; i < result; i++)
                cout << number[i];
            cout << "\n";
        }

    }
}

int FindNumber(int remainder, int index, int mod) {
    if(remainder == 0 && (index > 4 || GetVal(index - 1) >= mod))
        return index;
    if((index == 100 || appear[remainder]))
        return -1;
    if(index < 99)
        appear[remainder] = true;
    number[index] = 1;
    int result = FindNumber((remainder * 10 + 1) % mod, index + 1, mod);
    if(result == -1) {
        number[index] = 0;
        result = FindNumber((remainder * 10) % mod, index + 1, mod);
    }
    return result;
}

int GetVal(int layer) {
    int result = 0;
    int mult = 1;
    for(int i = layer; i >= 0; i--) {
        result += (int)(number[i]) * mult;
        mult = mult * 10;
    }
    return result;
}
