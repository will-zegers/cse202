#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

typedef int_fast32_t fast_int;

const fast_int N_MIN  = 1;
const fast_int N_MAX  = fast_int(1e5);
const fast_int A_MIN  = 1;
const fast_int A_MAX  = fast_int(1e9);
const fast_int N_ITER = 1e5;

fast_int partition2(vector<fast_int> &a, fast_int l, fast_int r) {
    fast_int x = a[l];
    fast_int j = l;
    for (fast_int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {
            j++;
            swap(a[i], a[j]);
        }
    }
    swap(a[l], a[j]);
    return j;
}

void randomized_quick_sort2(vector<fast_int> &a, fast_int l, fast_int r) {
    if (l >= r) {
        return;
    }

    fast_int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    fast_int m = partition2(a, l, r);

    randomized_quick_sort2(a, l, m - 1);
    randomized_quick_sort2(a, m + 1, r);
}

void partition3(vector<fast_int> &a, fast_int l, fast_int r, fast_int &m1, fast_int &m2) {
    fast_int x = a[l];
    size_t i;

    m1 = l;
    m2 = l;

    for (i = l + 1; i <= r; i++) {
        if (a[i] < x) {
            ++m2;
            swap(a[i], a[m2]);
        } else if (a[i] == x) {
            ++m1;
            ++m2;
            swap(a[i], a[m2]);
            swap(a[m2], a[m1]);
        }
    }
    for (i = l; i <= m1; ++i) {
        swap(a[i], a[m2-(i-l)]);
    }
    m1 = m2 - m1 + l;
}

void randomized_quick_sort3(vector<fast_int> &a, fast_int l, fast_int r) {
    if (l >= r) {
        return;
    }

    fast_int m1, m2;

    fast_int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    partition3(a, l, r, m1, m2);

    randomized_quick_sort3(a, l, m1 - 1);
    randomized_quick_sort3(a, m2 + 1, r);
}

void test_solution() {
    srand(1234);

    size_t i, j, k;
    int_fast32_t n;

    for (i = 0; i < N_ITER; ++i) {

        n = 10; //(rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<int_fast32_t> a(n), b(n), c(n);
        for (j = 0; j < a.size(); ++j) {
            a[j] = (rand() % (A_MAX + 1 - A_MIN)) + A_MIN;
            b[j] = a[j];
            c[j] = a[j];
        }

        randomized_quick_sort2(b, 0, b.size()-1);
        randomized_quick_sort3(c, 0, c.size()-1);

        for (j = 0; j < a.size(); ++j) {
            if (b[j] != c[j]) {
                std::cout << "[-] Error: (" << i << ")" << std::endl;
                std::cout << "  Input:";
                for (k = 0; k < a.size(); ++k) {
                    std::cout << " " << a[k];
                }
                std::cout << std::endl;
                std::cout << "  QS2: ";
                for (k = 0; k < b.size(); ++k) {
                    std::cout << " " << b[k];
                }
                std::cout << std::endl;
                std::cout << "  QS3: ";
                for (k = 0; k < c.size(); ++k) {
                    std::cout << " " << c[k];
                }
                std::cout << std::endl;
                return;
            }
        }
        std::cout << "[+] OK (" << i << ")" << std::endl;
    }
}

void test_timing() {
    srand(1234);

    size_t i, j;
    int_fast32_t n;

    for (i = 0; i < N_ITER; ++i) {

        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<int_fast32_t> a(n);
        for (j = 0; j < a.size(); ++j) {
            a[j] = (rand() % (A_MAX + 1 - A_MIN)) + A_MIN;
        }

        randomized_quick_sort3(a, 0, a.size()-1);
        std::cout << "[+] OK (" << i << ")" << std::endl;
    }
}

int main() {
//    test_solution();
//    test_timing();
    fast_int n;
    std::cin >> n;
    vector<fast_int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort3(a, 0, a.size()-1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
