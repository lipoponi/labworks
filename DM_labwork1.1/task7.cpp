#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("permutations.in", "r+", stdin);
    freopen("permutations.out", "w+", stdout);
    int n;
    cin >> n;

    vector<int> mas(n);
    for (int i = 0; i < n; i++) {
        mas[i] = i + 1;
    }

    while (true) {
        for (int elem : mas) {
            cout << elem << " ";
        }

        cout<< endl;

        bool exit = true;

        for (int i = 1; i < mas.size(); i++) {
            if (mas[i - 1] < mas[i]) {
                exit = false;
            }
        }

        if (exit) {
            break;
        }

        int jj = -1, ll = -1;
        for (int j = mas.size() - 2; 0 <= j; j--) {
            if (mas[j] < mas[j + 1]) {
                jj = j;
                break;
            }
        }

        for (int l = mas.size() -1 ; 0 <= l; l--) {
            if (mas[jj] < mas[l]) {
                ll = l;
                break;
            }
        }

        swap(mas[jj], mas[ll]);

        reverse(mas.begin() + jj + 1, mas.end());
    }
    return 0;
}
/*
 1 2 3 4
 1 2 4 3

 */