#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
    
using namespace std;
    
const int highway_length = 100;
    
struct Car {
    int v, t, w;
    Car() : v(0), t(0), w(1) {}
    Car(int _v, int _t) : v(_v), t(_t), w(1) {}
    Car(int _v, int _t, int _w) : v(_v), t(_t), w(_w) {}
};
    
bool operator< (Car a, Car b) {
    if(a.t == b.t)
        return a.v < b.v;
    return a.t < b.t;
}
    
bool operator== (Car a, Car b) {
    return a.t == b.t && a.v == b.v;
}
    
void remove_duplicates(vector<Car>&cars) {
    sort(cars.begin(), cars.end());
    vector<Car>result;
    int n = cars.size();
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && cars[i] == cars[j])
            j++;
        result.emplace_back(cars[i].v, cars[i].t, j - i);
        i = j - 1;
    }
    cars = result;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n;
    while(cin >> n) {
        int result = 0;
        vector<Car>cars(n);
        for(int i = 0; i < n; i++)
            cin >> cars[i].t >> cars[i].v;
        remove_duplicates(cars);
        
        set<Car>relevant_cars;
        for(Car c : cars) {
            result = max(result, c.w);
            for(auto it = relevant_cars.begin(); it != relevant_cars.end(); ) {
                auto next = it; next++;
                if(highway_length + it -> v * it -> t < c.t * it -> v)
                    relevant_cars.erase(it);
                    
                it = next;
            }
            
            map<long double, int>m;
            for(Car a : relevant_cars) {
                
                if(a.v != c.v) {
                    long double meet_point =  (a.v * a.t - c.v * c.t) / (1.0 * a.v - c.v);
                    if(0 <= a.v * (meet_point - a.t) && a.v * (meet_point - a.t) <= highway_length) {
                        result = max(result, (m[meet_point] += a.w) + c.w);
                    }
                }
            }
            
            relevant_cars.insert(c);
        }
        
        cout << result << '\n';
    }
    
    return 0;
}
