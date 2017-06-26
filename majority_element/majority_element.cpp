#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

const int_fast32_t N_MIN = 1;
const int_fast32_t N_MAX = int_fast32_t(1e5);
const int_fast32_t A_MIN = 0;
const int_fast32_t A_MAX = int_fast32_t(1e9);
const int_fast32_t N_ITER = int_fast32_t(1e5);

int_fast32_t get_majority_element_naive(vector<int_fast32_t> &a) {
    size_t i, j, half_a;
    int_fast32_t count;

    half_a = a.size() >> 1;
    for (i = 0; i < a.size(); ++i) {
        count = 0;
        for (j = 0; j < a.size(); ++j) {
            if (a[i] == a[j]) { ++count; }
        }

        if (count > half_a) { return a[i]; }
    }
    return -1;
}

int_fast32_t get_majority_element_fast(vector<int_fast32_t> &a, int_fast32_t left, int_fast32_t right) {

    size_t i, mid, half_a;
    int_fast32_t b, c, b_count, c_count;

    if (left == right) return -1;
    if (left + 1 == right) return a[left];

    //write your code here
    mid = ((size_t)left + right) >> 1;
    half_a = mid - left;
    b = get_majority_element_fast(a, left, mid);
    c = get_majority_element_fast(a, mid, right);

//    std::cout << left << " " << right << std::endl;
    if (b != -1) {
        if ( b == c) { return b; }
        b_count = 0;
        for (i = left; i < right; ++i) {
            if (a[i] == b) { ++b_count; }
//            std::cout << "b: " << a[i] << " " << (a[i] == b) << " " << b << " " << b_count << std::endl;
            if (b_count > half_a) { return b;}
        }
    }

    if (c != -1) {
        c_count = 0;
        for (i = left; i < right; ++i) {
            if (a[i] == c) { ++c_count; }
//            std::cout << "c: " << a[i] << " " << (a[i] == c) << " " << c << " " << c_count << std::endl;
            if (c_count > half_a) { return c;}
        }
    }

    return -1;
}

void test_solution() {
    srand(1234);

    size_t i, j;
    int_fast32_t naive, fast;
    int_fast32_t n;

    for (i = 0; i < N_ITER; ++i) {

        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<int_fast32_t> a(n);
        for (j = 0; j < a.size(); ++j) {
            a[j] = (rand() % (A_MAX + 1 - A_MIN)) + A_MIN;
        }

        fast = get_majority_element_fast(a, 0, a.size());
        naive = get_majority_element_naive(a);

        if ((fast != -1) != (naive != -1)) {
            std::cout << "[-] Error: (" << i << ")" << std::endl;
            std::cout << "  Input:";
            for (j = 0; j < a.size(); ++j) {
                std::cout << " " << a[j];
            }
            std::cout << std::endl;
            std::cout << "  Naive: " << naive << std::endl;
            std::cout << "  Fast: " << fast << std::endl;
            break;
        }
        std::cout << "[+] OK (" << i << ")" << std::endl;
//        std::cout << "  Naive: " << naive << std::endl;
//        std::cout << "  Fast: " << fast << std::endl;
    }
}

void test_timing() {
    srand(1234);

    size_t i, j;
    int_fast32_t fast;
    int_fast32_t n;

    for (i = 0; i < N_ITER; ++i) {

        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<int_fast32_t> a(n);
        for (j = 0; j < a.size(); ++j) {
            a[j] = (rand() % (A_MAX + 1 - A_MIN)) + A_MIN;
        }

        fast = get_majority_element_fast(a, 0, a.size());
        std::cout << "[+] OK (" << i << ")" << std::endl;
    }
}

int main() {
//    test_solution();
//    test_timing();
    int_fast32_t n;
    std::cin >> n;
    vector<int_fast32_t> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element_fast(a, 0, a.size()) != -1) << '\n';
    return 0;
}
