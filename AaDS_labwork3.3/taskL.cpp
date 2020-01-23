#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define int int64_t

vector<int> prefixFn(const string &str) {
    vector<int> suffix(str.size() + 1, 0);
    suffix[0] = -1;

    for (int i = 0; i < str.size(); i++) {
        char ch = str[i];

        int p = suffix[i];
        while (p != -1 && str[p] != ch) {
            p = suffix[p];
        }
        suffix[i + 1] = p + 1;
    }

    vector<int> result;
    for (int i = 1; i < suffix.size(); i++) {
        result.push_back(suffix[i]);
    }

    return result;
}

bool check(vector<int> &p, int period) {
    if (p.size() % period != 0) {
        return false;
    }

    int b = period;
    for (int ptr = period - 1 + period; ptr < p.size(); ptr += period) {
        if (p[ptr] != b) {
            return false;
        }
        b += period;
    }

    return true;
}

int min_period(const string &str) {
    vector<int> p = prefixFn(str);
    for (int i = 1; i <= str.size(); i++) {
        if (check(p, i)) {
            return i;
        }
    }
}


vector<int> mass(string str) {
    int n = str.size();

    vector<int> pc(n), cnt(256), cc(n);
    for (int i = 0; i < n; ++i)
        ++cnt[str[i]];
    for (int i = 1; i < 256; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i)
        pc[--cnt[str[i]]] = i;
    cc[pc[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; ++i) {
        if (str[pc[i]] != str[pc[i - 1]]) ++classes;
        cc[pc[i]] = classes - 1;
    }

    for (int k = 0; (1 << k) < n; k++) {
        vector<int> p(n, 0), c(n, 0);
        for (int i = 0; i < n; i++) {
            p[i] = (pc[i] - (1<<k) + n) % n;
        }

        cnt.assign(n, 0);
        for (int i = 0; i < n; i++) {
            ++cnt[cc[p[i]]];
        }
        for (int i = 1; i < n; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; 0 <= i; i--) {
            pc[--cnt[cc[p[i]]]] = p[i];
        }

        c[pc[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            if (make_pair(cc[pc[i]], cc[(pc[i] + (1<<k)) % n]) !=
                make_pair(cc[pc[i - 1]], cc[(pc[i - 1] + (1<<k)) % n]))
                classes++;
            c[pc[i]] = classes - 1;
        }

        cc = std::move(c);
    }

    return pc;
}


int32_t main() {
    string str;
    getline(cin, str);
    int k;
    cin >> k;

    if (str.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    string period(str.begin(), str.begin() + min_period(str));
    vector<int> p = mass(period);

    if (p.size() < k) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        int offset = p[k - 1];
        for (int i = 0; i < str.size(); i++) {
            cout << str[(i + offset) % str.size()];
        }
        cout << endl;
    }

    return 0;
}