#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cassert>

using std::vector;

const uint8_t PISANO_T = 60;
const uint16_t SEED = 1234;
const uint64_t MAX_N = 1e8;
const uint64_t MAX_M = MAX_N;

int64_t get_fibonacci_partial_sum_naive(long long from, long long to) {
    if (to <= 1)
        return to;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 2; i <= from ; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
    }

    long long sum = current;

    for (long long i = 0; i < to - from; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum += current;
    }

    return sum % 10;
}

inline int64_t get_sum_last_digit(uint64_t n) {

    int64_t i, n_plus2_mod, last_digit;

    n_plus2_mod = (n + 2) % PISANO_T;

    int32_t F[n_plus2_mod];
    F[0] = 0;
    F[1] = 1;
    for (i = 2; i <= n_plus2_mod; ++i) {
        F[i] = (F[i-1] + F[i-2]) % 10;
    }

    last_digit = (int64_t)(F[n_plus2_mod] - 1);
    return (last_digit >= 0) ? last_digit : 9;
}

int64_t get_fibonacci_partial_sum_fast(uint64_t from, uint64_t to) {

    int64_t to_last_digit, from_last_digit;

    to_last_digit = get_sum_last_digit(to);
    from_last_digit = get_sum_last_digit(from-1);

    to_last_digit += (to_last_digit < from_last_digit) ? 10 : 0;
    return to_last_digit - from_last_digit;
}

uint64_t rand64() {
    uint64_t i, j;
    i = (uint64_t)rand();
    j = (uint64_t)rand();

    return i * j;
}

void test_solution() {
    uint8_t i;
    int64_t m, n, naive, fast;

    srand(SEED);
    for (i = 0; i < 20; ++i) {
        m = rand() % MAX_M;
        n = (rand() % (MAX_N - m)) + m;

        std::cout << "m: " << m << " n: " << n << std::endl;
        naive = get_fibonacci_partial_sum_naive(m, n);
        fast = get_fibonacci_partial_sum_fast(m, n);
        std::cout << "Naive: " << naive << " Fast: " << fast << std::endl;
        assert(naive == fast);
    }
}

int main() {
    long long from, to;
//    test_solution();
    std::cin >> from >> to;
//    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
