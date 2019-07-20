#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("nextvector.in", "r+", stdin);
    freopen("nextvector.out", "w+", stdout);
    string vec;
    cin >> vec;
    string dec(vec), inc(vec);

    if (vec.find('1') == -1) {
        dec = "-";
    }
    if (inc.find('0') == -1) {
        inc = "-";
    }


    reverse(dec.begin(), dec.end());
    reverse(inc.begin(), inc.end());

    int i = 0;
    while (inc != "-") {
        if (inc[i] == '0') {
            inc[i]++;
            break;
        } else {
            inc[i] = '0';
            i++;
        }
    }

    i = 0;
    while (dec != "-") {
        if (dec[i] == '1') {
            dec[i] = '0';
            break;
        } else {
            dec[i] = '1';
            i++;
        }
    }

    reverse(dec.begin(), dec.end());
    reverse(inc.begin(), inc.end());

    cout << dec << endl << inc;
    return 0;
}