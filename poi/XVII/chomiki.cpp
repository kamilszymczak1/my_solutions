#include <iostream>

using namespace std;

const int MAX_L = 100001;
const int MAX_N = 200;
const long long inf = 9999999999999999;

string names[MAX_N];
int PI[MAX_L];
long long dist[MAX_N][MAX_N], minDist[30][MAX_N][MAX_N], bestDist[MAX_N], newDist[MAX_N];
int n, m;

void ReadData(), CalcDist();
int maxBorder(string s);
long long getResult();

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    ReadData();
    
    CalcDist();
    
    long long result = getResult();
    
    cout << result << '\n';
    
    return 0;        
}

long long getResult() {
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            minDist[0][i][j] = dist[i][j];
    
    int x = 2;
    for(int z = 1; x <= m; z++, x <<= 1) {
        for(int i = 0; i < n; i++)
            fill(minDist[z][i], minDist[z][i] + n, inf);
        
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++)
                    minDist[z][i][j] = min(minDist[z][i][j], minDist[z - 1][i][k] + minDist[z - 1][k][j]);
    }

    for(int i = 0; i < n; i++)
        bestDist[i] = names[i].size();
    
    for(int z = 30; z >= 0; z--) {
        if(m >= (1 << z)) {
            m = m - (1 << z);
            fill(newDist, newDist + n, inf);
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    newDist[i] = min(newDist[i], bestDist[j] + minDist[z][j][i]);
            swap(newDist, bestDist);
        }
    }
    long long result = inf;
    for(int i = 0; i < n; i++)
        result = min(result, bestDist[i]);
    return result;
}

void CalcDist() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int border = i == j ? maxBorder(names[i]) : maxBorder(names[j] + "%" + names[i]);
            dist[i][j] = names[j].size() - (border == names[j].size() ? border - 1 : border);
        }
    }
}

void ReadData() {
    cin >> n >> m;
    m = m - 1;
    for(int i = 0; i < n; i++)
        cin >> names[i];
}

int maxBorder(string s) {
    int j = PI[0] = -1;
    for(int i = 1; i <= (int)s.size(); i++) {
        while(j >= 0 && s[i - 1] != s[j])
            j = PI[j];
        PI[i] = ++j;
    }
    return PI[s.size()];
}
