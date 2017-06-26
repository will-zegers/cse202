#include <iostream>
#include <cassert>

const int SEED = 1234;
const unsigned long long M_MAX = 10e5;
const unsigned long long N_MAX = 10e9;

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
    }

    return current;
}

long long get_fibonacci_huge_fast(long long n, long long m) {

    long long i, pi, n_mod, previous, current, next;

    previous = 0;
    current = 1;

    pi = 0;
    while(1) {
        next = (previous + current) % m;
        previous = current;
        current = next;
        ++pi;
        if (previous == 0 && current == 1) {
            break;
        }
    }
    n_mod = n % pi;

    long long F[n_mod];
    F[0] = 0;
    F[1] = 1;
    for (i = 2; i <= n_mod; ++i) {
        F[i] = (F[i-1] + F[i-2]) % m;
    }

    return F[n_mod];
}

long long rand64() {
    long long i,j;

    i = (long long)rand();
    j = (long long)rand();
    return i * j;
}

void test_solution() {

    int i;
    long long m, n, naive, fast;
    srand(SEED);

    for (i = 0; i < 20; ++i) {
        m = rand() % M_MAX;
        n = rand64() % N_MAX;

        std::cout << "m: " << m << " n: " << n << std::endl;
        fast = get_fibonacci_huge_fast(n,m);
        naive = get_fibonacci_huge_naive(n,m);

        std::cout << "Naive: " << naive << " Fast: " << fast << std::endl;
        assert(naive == fast);
    }
}

int main() {
    long long n, m;
    std::cin >> n >> m;
//    test_solution();
//    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
