#include <iostream>
#include <stdlib.h>
#include <cassert>

const int SEED = 1234;

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {

    int t;

    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }

    return a;
}

void test_solution() {

    int a,b;

    srand(SEED);
    for (short n = 0; n < 20; ++n) {
        a = rand();
        b = rand();
        std::cout << "Testing " << a << " and " << b << "\n";
        std::cout << "GCD: " << gcd_fast(a,b) << " vs " << gcd_naive(a,b) << "\n";
        assert(gcd_fast(a,b) == gcd_naive(a,b));
    }
}

int main() {
  int a, b;
  std::cin >> a >> b;
//  test_solution();
//  std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
