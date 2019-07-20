#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("nextmultiperm.in", "r+", stdin);
    freopen("nextmultiperm.out", "w+", stdout);
    int n;
    cin >> n;
    vector<int> mas(n);

    for (int i = 0; i < n; i++) {
        cin >> mas[i];
    }

    vector<int> next(mas);

    if (is_sorted(next.rbegin(), next.rend())) {
        next = vector<int>(n, 0);
    } else {
        int jj = -1, ll = -1;
        for (int j = next.size() - 2; 0 <= j; j--) {
            if (next[j] < next[j + 1]) {
                jj = j;
                break;
            }
        }

        for (int l = next.size() -1 ; 0 <= l; l--) {
            if (next[jj] < next[l]) {
                ll = l;
                break;
            }
        }

        swap(next[jj], next[ll]);
        reverse(next.begin() + jj + 1, next.end());
    }

    for (int elem : next) {
        cout << elem << " ";
    }
    return 0;
}