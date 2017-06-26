#include <iostream>
#include <vector>
#include <algorithm>

#define DEBUG 0

using std::vector;

#if DEBUG
void stress_test(bool, bool);

const int32_t W_MIN = 1;
const int32_t W_MAX = int32_t(1e4);
const int32_t w_MIN = 0;
const int32_t w_MAX = int32_t(1e5);

const size_t N_MIN = 1;
const size_t N_MAX = size_t(3e2);
const size_t N_ITER = size_t(1e6);

const time_t T_MAX = 1*1000;
#endif

int32_t optimal_weight(int32_t W, vector<int32_t> &w) {

    int32_t val;
    vector< vector<int32_t> > value(w.size()+1, vector<int32_t>(W+1));

    int32_t current_weight, max_weight;

    size_t k = 0;
    for (size_t i = 1; i <= w.size(); ++i) {
        for (size_t j = 1; j <= W; ++j) {
            value[i][j] = value[i-1][j];
            if (j >= w[i-1]) {
                val = value[i-1][j-w[i-1]] + w[i-1];
                if (val > value[i][j]) { value[i][j] = val; }
            }
        }
    }

    max_weight = 0;
    for (size_t i = 0; i <= w.size(); ++i) {
        current_weight = value[i][W];
        if (current_weight > max_weight) {
            max_weight = current_weight;
        }
    }

    return max_weight;
}

int main() {
#if DEBUG
    stress_test(false, true);
#else
    int32_t n, W;
    std::cin >> W >> n;
    vector<int32_t> w(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
#endif
}

#if DEBUG
void test_solution() {
//
//    int32_t n;
//    int32_t naive, fast;
//
//    for (size_t i = 0; i < N_ITER; ++i) {
//        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;
//
//        fast = optimal_weight(n);
//
//        if (naive != fast) {
//            std::cout << "[-] Mismatch (" << i << ")" << std::endl;
//
//            std::cout << "  n: " << n << std::endl;
//
////            std::cout << "  Naive: " << naive;
////            for (size_t j = 0; j < naive.size(); ++j) {
////                std::cout << naive[i] << " ";
////            }
////            std::cout << std::endl;
//
//            std::cout << "  Fast: ";
//            for (size_t j = 0; j < fast.size(); ++j) {
//                std::cout << fast[i] << " ";
//            }
//            std::cout << std::endl;
//            return;
//        }
//        std::cout << "[OK] (" << i << ")" << std::endl;
//    }
    return;
}

void test_timing() {

    clock_t t;
    int32_t n, W;

    for (size_t i = 0; i < N_ITER; ++i) {
        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;
        W = (rand() % (W_MAX + 1 - W_MIN)) + W_MIN;

        vector<int32_t> w(n);
        for (size_t j = 0; j < w.size(); ++j) {
            w[j] = (rand() % (w_MAX + 1 - w_MIN)) + w_MIN;
        }

        t = clock();
        optimal_weight(W, w);
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
#endif