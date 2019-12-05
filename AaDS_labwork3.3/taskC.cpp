#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string str;
  cin >> str;

  vector<int> z(str.size(), 0);
  int l = 0, r = 0;

  for (int i = 1; i < str.size(); i++) {
    z[i] = max(0, min(r - i, z[i-l]));
    while (i + z[i] < z.size() && str[z[i]] == str[i + z[i]]) {
      z[i]++;
    }
    if (r < z[i] + i) {
      r = z[i] + i;
      l = i;
    }
  }

  for (size_t i = 1; i < z.size(); i++) {
    cout << " " << z[i];
  }
  return 0;
}