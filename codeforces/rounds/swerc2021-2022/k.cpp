#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long double ld;

int SAMPLES = 2;

ld rand01() {
    return (rand() * 1.0) / RAND_MAX;
}

ld f(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3, ld a, ld b) {
    return sqrt((x1 - a) * (x1 - a) + (y1 - b) * (y1 - b)) +
           sqrt((x2 - a) * (x2 - a) + (y2 - b) * (y2 - b)) +
           sqrt((x3 - a) * (x3 - a) + (y3 - b) * (y3 - b));
}

ld EV(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3) {
    
//     printf("EV at (%Lf, %Lf), (%Lf, %Lf), (%Lf, %Lf)\n",
//         x1, y1, x2, y2, x3, y3
//     );
    
    ld x = (x1 + x2 + x3) / 3.0, y = (y1 + y2 + y3) / 3.0;
    ld F = f(x1, y1, x2, y2, x3, y3, x, y);
    bool ok;
    do {
        ok = false;
        for(int i = 0; i < SAMPLES; i++) {
            ld X = x + 0.5 - rand01(), Y = y + 0.5 - rand01();
            ld newF = f(x1, y1, x2, y2, x3, y3, X, Y);
            if(newF < F) {
                ok = true;
                x = X; y = Y;
                F = newF;
                break;
            }
        }
    } while(ok);
    return F;
}

ld Calc(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3, ld x, ld y) {
    return max({EV(x1, y1, x2, y2, x, y),
                EV(x1, y1, x3, y3, x, y),
                EV(x2, y2, x3, y3, x, y)});
}

ld Compute(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3) {
    ld minX = min({x1, x2, x3}), maxX = max({x1, x2, x3});
    ld minY = min({y1, y2, y3}), maxY = max({y1, y2, y3});
    ld x = minX + rand01() * (maxX - minX),  y = minY + rand01() * (maxY - minY);
    ld answer = Calc(x1, y1, x2, y2, x3, y3, x, y);
    
    bool ok;
    do {
        ok = false;
        for(int i = 0; i < SAMPLES; i++) {
            ld X = x + 0.5 - rand01(), Y = y - 0.5 - rand01();
            long double newAnswer = Calc(x1, y1, x2, y2, x3, y3, X, Y);
            if(newAnswer < answer) {
                ok = true;
                x = X; y = Y;
                answer = newAnswer;
                break;
            }
        }
    } while(ok);
    return answer;
}

int main() {
    srand(time(NULL));
    int x1, y1, x2, y2, x3, y3;
    scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
    long double answer = Compute(x1, y1, x2, y2, x3, y3);
    for(int i = 0; i < 100000; i++)
        answer = min(answer, Compute(x1, y1, x2, y2, x3, y3));
    
    printf("%.10Lf\n", answer);
    
    return 0;
}
