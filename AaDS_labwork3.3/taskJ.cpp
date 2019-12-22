#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define int int64_t

vector<int> sufmass(string str) {
    str.push_back('#');
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

    for (int k = 2; k <= str.size(); k <<= 1) {
        vector<int> p(n, 0), c(n, 0);
        for (int i = 0; i < n; i++) {
            p[i] = (pc[i] - k / 2 + n) % n;
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
            if (make_pair(cc[pc[i]], cc[(pc[i] + k / 2) % n]) !=
                make_pair(cc[pc[i - 1]], cc[(pc[i - 1] + k / 2) % n]))
                classes++;
            c[pc[i]] = classes - 1;
        }

        cc = std::move(c);
    }

    return vector<int>(pc.begin() + 1, pc.end());
}

vector<int> lecepe(const vector<int> &p, const string &str) {
    int n = p.size();
    vector<int> rp(n);
    for (int i = 0; i < n; i++) {
        rp[p[i]] = i;
    }

    vector<int> h(n, 0);

    for (int i = 0; i < n; i++) {
        if (rp[i] == 0) continue;
        int a = i, b = p[rp[i] - 1];

        int off = h[rp[i]];
        while (off + a < str.size() && off + b < str.size() && str[a + off] == str[b + off]) {
            h[rp[i]] = ++off;
        }

        if (i + 1 < n && 0 < h[rp[i]]) {
            h[rp[i + 1]] = h[rp[i]] - 1;
        }
    }

    return vector<int>(h.begin() + 1, h.end());
}

int32_t main() {
    string str;
    cin >> str;

    vector<int> p = sufmass(str);
    vector<int> lcp = lecepe(p, str);

    for (int &v : p) {
        cout << v + 1 << " ";
    }
    cout << endl;

    for (int &l : lcp) {
        cout << l << " ";
    }
    cout << endl;

    return 0;
}