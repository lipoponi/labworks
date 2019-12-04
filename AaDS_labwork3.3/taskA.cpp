#include <iostream>
#include <vector>

using namespace std;

typedef int_fast64_t lnt;

const lnt mod1 = 1e9 + 7, base1 = 37;
const lnt mod2 = 1e9 + 9, base2 = 29;

int main() {
  string str;
  size_t m;
  cin >> str >> m;

  for (char &c : str) {
    c -= 'a';
  }

  vector<lnt> power1(str.size(), 0), power2(str.size(), 0);
  vector<lnt> hash1(str.size(), 0), hash2(str.size(), 0);
  power1[0] = power2[0] = 1;
  hash1[0] = hash2[0] = str[0];

  for (int i = 1; i < str.size(); i++) {
    power1[i] = (power1[i - 1] * base1) % mod1;
    power2[i] = (power2[i - 1] * base2) % mod2;
    hash1[i] = (hash1[i - 1] + power1[i] * str[i]) % mod1;
    hash2[i] = (hash2[i - 1] + power2[i] * str[i]) % mod2;
  }

  for (int i = 0; i < m; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--, c--, d--;

    lnt ah1 = ((hash1[b] - hash1[a] + 2 * mod1) * power1[c]) % mod1;
    lnt ch1 = ((hash1[d] - hash1[c] + 2 * mod1) * power1[a]) % mod1;

    lnt ah2 = ((hash2[b] - hash2[a] + 2 * mod2) * power2[c]) % mod2;
    lnt ch2 = ((hash2[d] - hash2[c] + 2 * mod2) * power2[a]) % mod2;

    if (ah1 == ch1 && ah2 == ch2 && str.substr(a, b - a + 1) == str.substr(c, d - c + 1)) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
  return 0;
}