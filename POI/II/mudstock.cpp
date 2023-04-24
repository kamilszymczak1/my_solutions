#include <iostream>

#define MAX_L 350

#define MAX_M 101

using namespace std;


typedef long long ll;

struct LineInfo {
    int cities;
    long long cost;
    int citizens;
};

ll dist[MAX_L][MAX_M];
ll citizens[MAX_L][MAX_M];
LineInfo line[MAX_L];
ll capital;

LineInfo LoadLine(int index);

int main() {
    ios_base::sync_with_stdio(0);
    
    int l;
    cin >> l >> capital;
    
    int totalCost = 0;
    int totalCitizens = capital;
    
    for(int i = 0; i < l; i++) {
        line[i] = LoadLine(i);
        totalCost += line[i].cost;
        totalCitizens += line[i].citizens;
    }
    
    for(int i = 0; i < l; i++)
        citizens[i][0] = totalCitizens - line[i].citizens;
    
    int result = totalCost;
    int resultL = 0;
    int resultM = 0;
    
    for(int i = 0; i < l; i++) {
        long long leftCost = totalCost - line[i].cost;
        long long rightCost = line[i].cost;
        long long leftCitizens = 0;
        long long rightCitizens = line[i].citizens;
        
        for(int j = 1; j <= line[i].cities; j++) {
            leftCitizens += citizens[i][j - 1];
            leftCost += leftCitizens * dist[i][j];
            rightCost -= rightCitizens * dist[i][j];
            rightCitizens -= citizens[i][j];
            if(leftCost + rightCost <= result) {
                result = leftCost + rightCost;
                resultL = i + 1;
                resultM = j;
            }
        }
    }
    
    cout << result << "\n" << resultL << ' ' << resultM << "\n";
    
    return 0;
}

LineInfo LoadLine(int index) {
    long long val, currDist = 0;
    LineInfo result = {0, 0, 0};
    cin >> result.cities;
    
    for(int i = 1; i <= result.cities; i++) {
        cin >> dist[index][i] >> citizens[index][i];
        currDist += dist[index][i];
        result.citizens += citizens[index][i];
        result.cost += citizens[index][i] * currDist;
    }
    return result;
}
