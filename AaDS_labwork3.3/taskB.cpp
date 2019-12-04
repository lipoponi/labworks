#include <iostream>
#include <vector>

int main() {
  std::string str;
  std::cin >> str;

  std::vector<int> suffix(str.size() + 1, 0);
  suffix[0] = -1;

  for (int i = 0; i < str.size(); i++) {
    char ch = str[i];

    int p = suffix[i];
    while (p != -1 && str[p] != ch) {
      p = suffix[p];
    }
    suffix[i + 1] = p + 1;
  }

  for (int i = 1; i < suffix.size(); i++) {
    std::cout << suffix[i] << " ";
  }
  return 0;
}
