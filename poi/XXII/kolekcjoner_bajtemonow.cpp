#include "ckollib.h"

using namespace std;

int firstCard = 0, firstCardCount = 1;
int secondCard = 0, secondCardCount = 0;

int bitcnt[32];

void AddBits(int x) {
    for(int i = 0; i < 32; i++) {
        if(x & 1)
            bitcnt[i]++;
        x >>= 1;
    }
}

int NextCard() {
    int k = karta();
    AddBits(k);
    return k;
}

int main() {
    firstCard = NextCard();
    int k = NextCard();
    while(k == firstCard && k != 0) {
        firstCardCount++;
        k = NextCard();
    }
    secondCard = k;
    while(k != 0) {
        if(k == firstCard)
            firstCardCount++;
        if(k == secondCard)
            secondCardCount++;
        
        k = NextCard();
    }
    
    if(secondCard == 0) {
        odpowiedz(firstCard);
    } else if(firstCardCount != secondCardCount) {
        if(firstCardCount < secondCardCount) {
            odpowiedz(firstCard);
        } else {
            odpowiedz(secondCard);
        }
    } else {
        for(int i = 0; i < 32; i++) {
            bitcnt[i] %= firstCardCount;
        }
        int result = 0;
        for(int i = 0; i < 32; i++)
            if(bitcnt[i])
                result |= 1 << i;
        odpowiedz(result);
    }
    
    return 0;
}
