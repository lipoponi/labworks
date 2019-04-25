#include <bits/stdc++.h>

using namespace std;

unsigned int treeSize;
long long ***FT;

void build(unsigned int n) {
    treeSize = n;
    FT = new long long **[treeSize];

    for (int i = 0; i < treeSize; i++) {
        FT[i] = new long long *[treeSize];

        for (int j = 0; j < treeSize; j++) {
            FT[i][j] = new long long[treeSize];

            for (int k = 0; k < treeSize; k++) {
                FT[i][j][k] = 0;
            }
        }
    }
}

long long sum(int x, int y, int z) {
    long long result = 0;
    if (x == -1 || y == -1 || z == -1) return 0;
    for (int i = x; 0 <= i; i = (i & (i + 1)) - 1) {
        for (int j = y; 0 <= j; j = (j & (j + 1)) - 1) {
            for (int k = z; 0 <= k; k = (k & (k + 1)) - 1) {
                result += FT[i][j][k];
            }
        }
    }
    return result;
}

void add(int x, int y, int z, long long d) {
    for (int i = x; i < treeSize; i = (i | (i + 1))) {
        for (int j = y; j < treeSize; j = (j | (j + 1))) {
            for (int k = z; k < treeSize; k = (k | (k + 1))) {
                FT[i][j][k] += d;
            }
        }
    }
}

long long get(int x1, int y1, int z1, int x2, int y2, int z2) {
    x1--;
    y1--;
    z1--;
    long long a, b, c, d, e, f, g, h;
    a = sum(x1, y1, z1);
    b = sum(x1, y1, z2);
    c = sum(x1, y2, z1);
    d = sum(x2, y1, z1);
    e = sum(x1, y2, z2);
    f = sum(x2, y1, z2);
    g = sum(x2, y2, z1);
    h = sum(x2, y2, z2);
    return h - (e + f + g) + (b + c + d) - a;
}


int main() {
    unsigned int n;
    cin >> n;

    build(n);

    int m;
    while (cin >> m) {
        if (m == 1) {
            int x, y, z;
            long long d;
            cin >> x >> y >> z >> d;
            add(x, y, z, d);
        } else if (m == 2) {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << get(x1, y1, z1, x2, y2, z2) << endl;
        } else {
            break;
        }
    }
    return 0;
}