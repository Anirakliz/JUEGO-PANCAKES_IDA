#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Función para intercambiar dos elementos
void swap(vector<int>& v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// Función para calcular la heurística
int heuristic(const vector<int>& v) {
    int n = v.size();
    int h = 0;
    for (int i = 0; i < n - 1; i++) {
        if (v[i] + 1 != v[i + 1]) {
            h++;
        }
    }
    return h;
}

// Función IDA*
int IDAStar(vector<int>& v, int g, int bound) {
    int h = heuristic(v);
    int f = g + h;
    if (f > bound) {
        return f;
    }
    if (h == 0) {
        return -1;
    }
    int min_cost = INT_MAX;
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        if (v[i] + 1 == v[i + 1]) {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (v[i] + 1 == v[j]) {
                vector<int> u = v;
                swap(u, i, j);
                int cost = IDAStar(u, g + 1, bound);
                if (cost == -1) {
                    return cost;
                }
                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
        }
    }
    return min_cost == INT_MAX ? -1 : min_cost;
}

// Función principal
int main() {
    vector<int> v = {3, 1, 2, 4, 5};
    int bound = heuristic(v);
    while (true) {
        int cost = IDAStar(v, 0, bound);
        if (cost == -1) {
            cout << "Se encontró la solución." << endl;
            break;
        }
        bound = cost;
    }
    return 0;
}
