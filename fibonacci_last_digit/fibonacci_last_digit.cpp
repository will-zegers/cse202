#include <iostream>
#include <cassert>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {

    int i;
    int F[n];

    F[0] = 0;
    F[1] = 1;

    for (i = 2; i <= n; ++i) {
        F[i] = (F[i-1] + F[i-2]) % 10;
    }

    return F[n];
}

void test_solution() {
    for (short n = 0; n < 20; ++n) {
        assert(get_fibonacci_last_digit_fast(n) == get_fibonacci_last_digit_naive(n));
    }
}

int main() {
    int n;
    std::cin >> n;
    test_solution();
//    std::cout << (short)get_fibonacci_last_digit_naive(n) << '\n';
    std::cout << get_fibonacci_last_digit_fast(n) << '\n';
}
