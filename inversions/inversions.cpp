#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using std::vector;

const size_t N_MIN  = 1;
const size_t N_MAX  = size_t(1e5);
const size_t A_MIN  = 1;
const size_t A_MAX  = size_t(1e9);
const size_t T_MAX  = 3 * CLOCKS_PER_SEC;
const size_t N_ITER = size_t(1e3);

int_fast64_t merge(vector<int_fast32_t> &a, vector<int_fast32_t> &b, vector<int_fast32_t> &c) {

    size_t i, j, k;
    int_fast64_t inv_count;

    inv_count = 0;
    for (i=0, j=0, k=0; j < a.size() && k < b.size(); ++i) {
        if (a[j] <= b[k]){
            c[i] = a[j];
            ++j;
        } else {
            inv_count += a.size() - j;
            c[i] = b[k];
            ++k;
        }
    }

    for (; j < a.size(); ++j) {
        c[i] = a[j];
        ++i;
    }

    for (; k < b.size(); ++k) {
        c[i] = b[k];
        ++i;
    }

    return inv_count;
}

int_fast64_t get_number_of_inversions_fast(vector<int_fast32_t> &a, size_t left, size_t right, vector<int_fast32_t> &z) {

    size_t mid;
    int_fast64_t inv_count;

    inv_count = 0;
    if (left+1 == right) { z = {a[left]}; return inv_count; }

    mid = (left + right) >> 1;

    vector<int_fast32_t> l_vec(mid-left), r_vec(right-mid); //, merged(right-left);
    inv_count += get_number_of_inversions_fast(a, left, mid, l_vec);
    inv_count += get_number_of_inversions_fast(a, mid, right, r_vec);

    inv_count += merge(l_vec, r_vec, z);
    return inv_count;
}

int_fast64_t get_number_of_inversions_naive(vector<int_fast32_t> &a) {
    size_t i, j;
    int_fast64_t count;

    count = 0;
    for (i = 0; i < a.size(); ++i) {
        for (j = i+1; j < a.size(); ++j) {
            if (a[i] > a[j]) { ++count; }
        }
    }

    return count;
}

void test_solution() {
    srand(1235);

    size_t i, j, k, n;
    int_fast64_t naive, fast;

    for (i = 0; i < N_ITER; ++i) {

        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<int_fast32_t> a(n), b(n), c(n);
        for (j = 0; j < a.size(); ++j) {
            a[j] = (rand() % (A_MAX + 1 - A_MIN)) + A_MIN;
            b[j] = a[j];
        }

        naive = get_number_of_inversions_naive(a);
        fast = get_number_of_inversions_fast(a, 0, a.size(), c);

//        for (j = 0; j < a.size(); ++j) {
            if (fast != naive) {
                std::cout << "[-] Error: (" << i << ")" << std::endl;
                std::cout << "  Input:";
                for (k = 0; k < a.size(); ++k) {
                    std::cout << " " << a[k];
                }
                std::cout << std::endl;
                std::cout << "  Naive: " << naive << std::endl;
                std::cout << "  Fast: " << fast << std::endl;
                std::cout << std::endl;
                return;
            }
//        }
        std::cout << "[+] OK (" << i << ")" << std::endl;
    }
}

void test_timing() {
    srand(1234);

    size_t i, j, n;
    clock_t t;

    for (i = 0; i < N_ITER; ++i) {

        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<int_fast32_t> a(n), b(n);
        for (j = 0; j < a.size(); ++j) {
            a[j] = (rand() % (A_MAX + 1 - A_MIN)) + A_MIN;
        }

        t = clock();
        get_number_of_inversions_fast(a, 0, a.size(), b);
        t = clock() - t;
        if (t > T_MAX) {
            std::cout << "[-] Time exceeded (" << i << ")" << std::endl;
            std::cout << "    Time elapsed: " << (double)t/1000 << " s" << std::endl;
            break;
        }

        std::cout << "[+] OK (" << i << ") t=" << (double)t/1000 << " s" << std::endl;
    }
}

int main() {
//    test_solution();
//    test_timing();
    int_fast32_t n;
    std::cin >> n;

    vector<int_fast32_t> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int_fast32_t> b(a.size());

    std::cout << get_number_of_inversions_fast(a, 0, a.size(), b) << std::endl;
    return 0;
}
