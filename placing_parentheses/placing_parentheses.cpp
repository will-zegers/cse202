#include <iostream>
//#include <cassert>
#include <vector>
#include <limits>
#include <sstream>
#include <stdlib.h>

#define DEBUG 0

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

void stress_test(bool, bool);

const size_t SEED = 1237;
const size_t N_MIN = 1;
const size_t N_MAX = 5;
const size_t N_ITER = size_t(1e6);
const std::string INPUT = "1-0-1*1-0-1";
const std::string NUMS = "01";//2";//3456789";
const std::string OPS  = "+-*";

const time_t T_MAX = 1*1000;

static int g = 0;

#endif

using std::vector;

template <class T>
inline T min5(T a, T b, T c, T d, T e) {
    return std::min(std::min(std::min(a,b),std::min(c,d)), e);
}

template <class T>
inline T max5(T a, T b, T c, T d, T e) {
    return std::max(std::max(std::max(a,b),std::max(c,d)), e);
}

inline int64_t eval(int64_t a, int64_t b, char op) {
    if (op == '*') { return a * b; }
    else if (op == '+') { return a + b; }
    else if (op == '-') { return a - b; }
}


void naive_get_max_value(const std::string &exp, int64_t &min, int64_t &max) {

    char op;
    size_t n;
    std::string l, r;
    int64_t a, b, c, d, tmp, result, l_min, l_max, r_min, r_max;

    n = exp.size();
    if (n <= 1) {
        tmp = (int64_t)(exp[0] - '0');
        max = tmp;
        min = tmp;
        return;
    } else if (n <= 3) {
        a = (int64_t)(exp[0] - '0');
        op = exp[1];
        b = (int64_t)(exp[2] - '0');
        tmp = eval(a,b,op);
        max = tmp;
        min = tmp;
        return;
    }

    max = std::numeric_limits<int64_t>::min();
    min = std::numeric_limits<int64_t>::max();
    for (size_t i = 1; i < n; i += 2) {
        op = exp[i];
        l = exp.substr(0,i);
        r = exp.substr(i+1,n);
        naive_get_max_value(l, l_min, l_max);
        naive_get_max_value(r, r_min, r_max);
        a = eval(l_min, r_max, op);
        b = eval(l_min, r_max, op);
        c = eval(l_max, r_max, op);
        d = eval(l_max, r_min, op);

        max = max5(a,b,c,d,max);
        min = min5(a,b,c,d,min);
    }
}

int64_t get_max_value(const std::string &exp) {

    size_t i, j, k, n, s;
    int64_t a, b, c, d, min, max;

    n = (exp.size() + 1) >> 1;
    vector<char> op;
    vector< vector<int64_t> > M(n, vector<int64_t>(n));
    vector< vector<int64_t> > m(n, vector<int64_t>(n));


    for (i = 0, j = 0; j < exp.size()-1; ++i, ++j) {
        op.push_back(exp[2*i+1]);
    };

    for (i = 0; i < n; ++i) {
        M[i][i] = (int64_t)(exp[2*i] - '0');
        m[i][i] = (int64_t)(exp[2*i] - '0');
    }

    for (s = 1; s < n; ++s) {
        for (i = 0; i < n-s; ++i) {
            j = i + s;
            min = std::numeric_limits<int64_t>::max();
            max = std::numeric_limits<int64_t>::min();
            for (k = i; k < j; ++k) {
                a = eval(M[i][k], M[k+1][j], op[k]);
                b = eval(M[i][k], m[k+1][j], op[k]);
                c = eval(m[i][k], M[k+1][j], op[k]);
                d = eval(m[i][k], m[k+1][j], op[k]);
                min = min5(a,b,c,d,min);
                max = max5(a,b,c,d,max);
            }
            M[i][j] = max;
            m[i][j] = min;
        }
    }

    max = M[0][n-1];

    return max;
}

int main() {
#if DEBUG
    stress_test(true, false);

//    int64_t min, max;
//    std::string s = INPUT;
//    std::cout << get_max_value(s) << std::endl;
#else
    std::string s;
    std::cin >> s;
    std::cout << get_max_value(s) << '\n';
#endif
}

#if DEBUG

void test_solution() {

    int64_t n;
    int64_t fast, min, max;
    std::string str;

    for (size_t i = 0; i < N_ITER; ++i) {
        str = "";

        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;
        str +=  NUMS[rand() % NUMS.size()];
        for (size_t j = 0; j < n; ++j) {
            str += OPS[rand() % OPS.size()];
            str += NUMS[rand() % NUMS.size()];
        }

        fast = get_max_value(str);
        naive_get_max_value(str, min, max);

        if (max != fast) {
            std::cout << "[-] Mismatch (" << i << ")" << std::endl;

            std::cout << "  n: " << n << std::endl;
            std::cout << "  Input: " << str << std::endl;
            std::cout << "  Naive: " << max << std::endl;
            std::cout << "  Fast: " << fast << std::endl;
            return;
        }
        ++g;
        std::cout << "[OK] (" << i << ")" << std::endl;
    }
    return;
}

void test_timing() {

    clock_t t;
    size_t n;
    std::string str;

    for (size_t i = 0; i < N_ITER; ++i) {
        str = "";

        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;
        str +=  NUMS[rand() % NUMS.size()];
        for (size_t j = 0; j < n; ++j) {
            str += OPS[rand() % OPS.size()];
            str += NUMS[rand() % NUMS.size()];
        }
        t = clock();
        get_max_value(str);
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
    std::cout << "DONE" << std::endl;
}

void stress_test(bool testSolution, bool testTiming) {
    srand(SEED);
    if (testSolution) { test_solution(); }
    if (testTiming) { test_timing(); }
}
#endif
