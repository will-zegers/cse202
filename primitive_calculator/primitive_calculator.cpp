#include <iostream>
#include <vector>
#include <algorithm>

#define DEBUG 0

using std::vector;

void stress_test(bool, bool);

const size_t N_MIN = 1;
const size_t N_MAX = size_t(1e6);
const size_t N_ITER = size_t(1e6);
const time_t T_MAX = 1*1000;

vector<int_fast32_t> optimal_sequence(int_fast32_t n) {

    std::vector<int_fast32_t> sequence;
    std::vector<int_fast32_t> lut = {0, 0};
    int_fast32_t ops;

    for (size_t i = 2; i <= n; ++i) {
        ops = lut[i-1];
        if (i % 3 == 0) { ops = std::min(ops, lut[(i)/3]); }
        if (i % 2 == 0) { ops = std::min(ops, lut[(i)/2]); }
        lut.push_back(ops+1);
    }

    int_fast32_t n_by_2, n_by_3, n_minus_1;
    while(n > 1) {
        sequence.push_back(n);

        n_by_3 = n/3;
        n_by_2 = n>>1;
        n_minus_1 = n-1;
        ops = std::numeric_limits<int_fast32_t>::max();

        if (n % 3 == 0 && ops > lut[n_by_3]) {
            n = n_by_3;
            ops = lut[n_by_3];
        }
        if (n % 2 == 0 && ops > lut[n_by_2]) {
            n = n_by_2;
            ops = lut[n_by_2];
        }
        if (ops > lut[n_minus_1]) {
            n = n_minus_1;
        }
    }

    sequence.push_back(1);
    std::reverse(sequence.begin(), sequence.end());
    return sequence;
}
int main() {

#if DEBUG
    stress_test(false, true);
#else
    int n;
    std::cin >> n;
    vector<int_fast32_t> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
#endif
}

void test_solution() {

    int_fast32_t n;
    vector<int_fast32_t> naive, fast;

    for (size_t i = 0; i < N_ITER; ++i) {
        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        fast = optimal_sequence(n);

        if (naive != fast) {
            std::cout << "[-] Mismatch (" << i << ")" << std::endl;

            std::cout << "  n: " << n << std::endl;

//            std::cout << "  Naive: " << naive;
//            for (size_t j = 0; j < naive.size(); ++j) {
//                std::cout << naive[i] << " ";
//            }
//            std::cout << std::endl;

            std::cout << "  Fast: ";
            for (size_t j = 0; j < fast.size(); ++j) {
                std::cout << fast[i] << " ";
            }
            std::cout << std::endl;
            return;
        }
        std::cout << "[OK] (" << i << ")" << std::endl;
    }
}

void test_timing() {

    size_t i;
    clock_t t;
    int_fast32_t n;

    for (i = 0; i < N_ITER; ++i) {
        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        t = clock();
        optimal_sequence(n);
        t = clock() - t;

        if (t > T_MAX) {
            std::cout << "[-] Time exceeded (" << i << ")" << std::endl;
            std::cout << "    Time elapsed: " << (double)t/1000 << " s" << std::endl;
            break;
        } else if (t > T_MAX*0.9) {
            std::cout << "[!] Warning (" << i << ") t=" << (double)t/1000 << " s" << std::endl;
        }

        std::cout << "[+] OK (" << i << ") t=" << (double)t/1000 << " s" << std::endl;
    }
}

void stress_test(bool testSolution, bool testTiming) {
    srand(1234);
    if (testSolution) { test_solution(); }
    if (testTiming) { test_timing(); }
}
