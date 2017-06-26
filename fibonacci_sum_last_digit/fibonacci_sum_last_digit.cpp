#include <iostream>
#include <cassert>
#include <stdint.h>

const uint32_t SEED = 1234;
const uint64_t N_MAX = 1e14;
const uint8_t PISANO_T = 60;

uint32_t fibonacci_sum_naive(uint64_t n) {

    uint64_t i, previous, current, next, sum;

    if (n <= 1) {
        return n;
    }

    previous = 0;
    current = 1;
    sum = 1;

    for (i = 2; i <= n; ++i) {
        next = (current + previous) % 10;
        previous = current;
        current = next;
        sum = (sum + current) % 10;
    }

    return sum;
}

uint32_t fibonacci_sum_fast(uint64_t n) {

    uint64_t i, pi, n_plus2_mod;

    n_plus2_mod = (n + 2) % PISANO_T;

    int8_t F[n_plus2_mod], last_digit;
    F[0] = 0;
    F[1] = 1;
    for (i = 2; i <= n_plus2_mod; ++i) {
        F[i] = (F[i-1] + F[i-2]) % 10;
    }

    last_digit = F[n_plus2_mod] - 1;
    return (last_digit >= 0) ? last_digit : 9;
}

uint64_t rand64() {
    uint64_t i, j;
    i = (uint64_t)rand();
    j = (uint64_t)rand();
    return i * j;
}

void test_solution() {
    uint8_t i;
    uint64_t n, naive, fast;

    srand(SEED);
    for (i = 0; i < 20; ++i) {
        n = rand64() % N_MAX;
        std::cout << "n: " << n << std::endl;
        fast = fibonacci_sum_fast(n);
        naive = fibonacci_sum_naive(n);
        std::cout << "Fast: " << fast << " Naive: " << naive << std::endl;
        assert(fast == naive);
    }
}

int main() {
    uint64_t n = 0;

//    test_solution();
    std::cin >> n;
//    std::cout << fibonacci_sum_naive(n);
    std::cout << fibonacci_sum_fast(n);
}
