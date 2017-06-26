#include <iostream>

int get_change(int m) {
  int n;

  while (m >= 10) {
    m -= 10;
    ++n;
  }

  if (m >= 5) {
    m -= 5;
    ++n;
  }

  while (m > 0) {
    --m;
    ++n;
  }

  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
