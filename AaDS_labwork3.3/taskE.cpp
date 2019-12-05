#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefixFn(string &str) {
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

int main() {
  string str;
  cin >> str;

  vector<int> p = prefixFn(str);
  for (int i = 1; i <= str.size(); i++) {
    if (check(p, i)) {
      cout << i << endl;
      return 0;
    }
  }

  cout << -1 << endl;
  return 0;
}