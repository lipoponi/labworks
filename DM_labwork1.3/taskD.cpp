#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<double>> multiply(vector<vector<double>> &a, vector<vector<double>> &b) {
    vector<vector<double>> result(a.size(), vector<double>(a.size()));

    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            result[i][j] = 0;
            for (int k = 0; k < a.size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

int main() {
#ifndef DEBUG
    freopen("markchain.in", "r+", stdin);
    freopen("markchain.out", "w+", stdout);
#endif

    unsigned int n;
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n));
    for (vector<double> &row : matrix) {
        for (double &cell : row) {
            cin >> cell;
        }
    }

    bool bad = true;
    while (bad) {
        bad = false;

        vector<vector<double>> sq = multiply(matrix, matrix);
        for (int i = 0; i < n && !bad; i++) {
            for (int j = 0; j < n && !bad; j++) {
                if (0.0001 <= abs(sq[i][j] - matrix[i][j])) {
                    bad = true;
                }
            }
        }

        if (bad) {
            matrix = sq;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << fixed;
        cout << setprecision(6) << matrix[0][i] << endl;
    }
    return 0;
}