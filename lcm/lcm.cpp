#include <iostream>
#include <cassert>

const int SEED = 1234;

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long lcm_fast(int a, int b) {

    long long prod;
    int t;

    prod = (long long)a * b;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }

    return prod / a;
}

void test_solution() {
    int a, b, i;
    long long naive, fast;

    srand(SEED);
    for (i = 0; i < 20; ++i) {
        std::cout << "Running test " << i << std::endl;
        a = rand() % 10000;
        b = rand() % 10000;

        naive = lcm_naive(a,b);
        fast = lcm_fast(a,b);
        assert(naive == fast);
        std::cout << "Naive: " << naive << " Fast: " << fast << std::endl;
    }
}

int main() {
  int a, b;
//  test_solution();
  std::cin >> a >> b;
//  std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
