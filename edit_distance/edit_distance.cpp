#include <iostream>
#include <string>
#include <vector>

#define DEBUG 0

using std::string;

#if DEBUG
void stress_test(bool, bool);

const size_t N_MIN = 1;
const size_t N_MAX = size_t(3e2);
const size_t N_ITER = size_t(1e6);

const time_t T_MAX = 1*1000;

static const char alphanum[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"};
#endif

int edit_distance(const string &A, const string &B) {
    //write your code here
    size_t i, j;
    int32_t insertion, deletion, match, mismatch;
    std::vector< std::vector<int32_t> > D(A.size()+1, std::vector<int32_t>(B.size()+1));

    for (i = 0; i <= A.size(); ++i) {
        D[i][0] = (int32_t)i;
    }
    for (i = 0; i <= B.size(); ++i) {
        D[0][i] = (int32_t)i;
    }

    for (i = 1; i <= A.size(); ++i) {
        for (j = 1; j <= B.size(); ++j) {
            insertion = D[i][j-1] + 1;
            deletion  = D[i-1][j] + 1;
            match     = D[i-1][j-1];
            if (A[i-1] != B[j-1]) {
                ++match;
            }
            D[i][j] = std::min(insertion, deletion);
            D[i][j] = std::min(D[i][j], match);
        }
    }

    return D[A.size()][B.size()];
}

int main() {
#if DEBUG
    stress_test();
#else
    string A;
    string B;
    std::cin >> A >> B;
    std::cout << edit_distance(A, B) << std::endl;
#endif
    return 0;

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
    int32_t n;

    std::string

    for (size_t i = 0; i < N_ITER; ++i) {
        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;


        t = clock();
        edit_distance(n);
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