#include <bits/stdc++.h>

using namespace std;

bool check(string brackets) {
    int balance = 0;

    for (char c : brackets) {
        if (c == '(') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            return false;
        }
    }

    return balance == 0;
}

int main() {
    freopen("nextbrackets.in", "r+", stdin);
    freopen("nextbrackets.out", "w+", stdout);
    string brackets;
    cin >> brackets;

    int balance = 0;
    bool hasNext = false;
    for (char c : brackets) {
        if (c == '(') {
            balance++;
        } else {
            balance--;
        }

        if (1 < balance) {
            hasNext = true;
        }
    }

    if (hasNext) {
        int i = brackets.size() - 1;
        balance = 0;

        for (; 0 <= i; i--) {
            if (brackets[i] == ')') {
                balance++;
            } else if (1 < balance) {
                brackets[i] = ')';
                break;
            } else {
                balance--;
            }
        }

        i++;
        for (int j = i; j < brackets.size(); j++) {
            brackets[j] = ')';
        }

        balance = 0;
        for (int j = 0; j < i; j++) {
            if (brackets[j] == '(') {
                balance++;
            } else {
                balance--;
            }
        }

        int opens = (brackets.size() - i - balance)/2;
        for (int j = 0; j < opens; j++) {
            brackets[j + i] = '(';
        }

        cout << brackets;
    } else {
        cout << "-" << endl;
    }
    return 0;
}