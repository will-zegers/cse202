#include <iostream>
#include <string>
#include <vector>
#include <limits>

#define DEBUG 0

using std::string;
using std::vector;

typedef int32_t data_t;

#if DEBUG

#define v1dump(V) \
    std::cout << "\t"; \
    for (size_t i = 0; i < V.size(); ++i) { \
        std::cout << V[i] << "\t"; \
    } \
    std::cout << std::endl; \

#define v2dump(V) \
    for (size_t i = 0; i < V.size(); ++i) { \
        for (size_t j =0; j < V.size(); ++j) { \
            std::cout << V[i][j] << "\t"; \
        } \
        std::cout << std::endl; \
    }

#define v3dump(V) \
    for (size_t q = 0; q < V.size(); ++q) { \
        for (size_t r = 0; r < V[0].size(); ++r) { \
            for (size_t s = 0; s < V[0][0].size(); ++s) { \
                std::cout << V[q][r][s] << "\t"; \
            } \
            std::cout << std::endl; \
            } \
        std::cout << "-------------------------" << std::endl; \
    }

void stress_test(bool, bool);

const size_t LMN_MIN = 1;
const size_t LMN_MAX = size_t(1e2);
const int32_t ABC_MIN = size_t(-1e9);
const int32_t ABC_MAX = size_t(1e9);
const size_t N_ITER = size_t(1e6);

const time_t T_MAX = 2*1000;;
#endif

template<class T>
inline T max3(T a, T b, T c) {
    return std::max(std::max(a,b), c);
}

data_t lc3(vector<data_t> A, vector<data_t> B, vector<data_t> C) {

    data_t insertion1, insertion2, deletion1, deletion2, p_match1, p_match2, match;
    std::vector< std::vector< std::vector<data_t> > >D(
            A.size()+1, std::vector< std::vector<data_t> >(
                    B.size()+1, std::vector<data_t>(C.size()+1)));

    for (size_t i = 1; i < A.size()+1; ++i) {
        for (size_t j = 1; j < B.size()+1; ++j) {
            for (size_t k = 1; k < C.size()+1; ++k) {

                insertion1 = D[i][j-1][k];
                insertion2 = D[i][j][k-1];
                deletion1 = D[i-1][j][k];
                deletion2 = D[i-1][j-1][k];
                p_match1 = D[i-1][j][k-1];
                p_match2 = D[i][j-1][k-1];
                match = D[i-1][j-1][k-1];

                if (A[i-1] == B[j-1] && B[j-1] == C[k-1]) {
                    ++match;
                }
                D[i][j][k] = max3(insertion1, deletion1, match);
                D[i][j][k] = max3(insertion2, deletion2, D[i][j][k]);
                D[i][j][k] = max3(p_match1, p_match2, D[i][j][k]);
            }
        }
    }

    return D[A.size()][B.size()][C.size()];
}

int main() {
#if DEBUG
    stress_test(false, true);
//    vector<data_t> a = {8,3,2,1,7};
//    vector<data_t> b = {8,2,1,3,8,10,7};
//    vector<data_t> c = {6,8,3,1,4,7};
//    std::cout << lc3(a, b, c) << std::endl;
#else
  size_t an;
  std::cin >> an;
  vector<data_t> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<data_t> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<data_t> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lc3(a, b, c) << std::endl;
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
    size_t l,m,n;
    for (size_t i = 0; i < N_ITER; ++i) {
        l= (rand() % (LMN_MAX + 1 - LMN_MIN)) + LMN_MIN;
        m = (rand() % (LMN_MAX + 1 - LMN_MIN)) + LMN_MIN;
        n = (rand() % (LMN_MAX + 1 - LMN_MIN)) + LMN_MIN;


        vector<data_t> a(l);
        for (size_t i = 0; i < a.size(); ++i) {
            a[i] = (rand() % (ABC_MAX + 1 - ABC_MIN)) + ABC_MIN;
        }
        vector<data_t> b(m);
        for (size_t i = 0; i < b.size(); ++i) {
            b[i] = (rand() % (ABC_MAX + 1 - ABC_MIN)) + ABC_MIN;
        }
        vector<data_t> c(n);
        for (size_t i = 0; i < c.size(); ++i) {
            c[i] = (rand() % (ABC_MAX + 1 - ABC_MIN)) + ABC_MIN;
        }

        t = clock();
        lc3(a,b,c);
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