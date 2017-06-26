#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

const int_fast32_t KN_MIN = 1;
const int_fast32_t KN_MAX = int_fast32_t(1e4);
const int_fast32_t AB_MIN = 1;
const int_fast32_t AB_MAX = int_fast32_t(1e9);
const int_fast32_t N_ITER = 1e3;

int_fast32_t binary_search(const vector<int_fast32_t> &a, int_fast32_t x) {
    int_fast32_t left, mid, right;

    left = 0, right = (int_fast32_t) a.size();
    while(1) {
        if (left >= right) {
            return -1;
        }

        mid = (left + right) >> 1;
//        std::cout << x << " " << mid << std::endl;
        if (x == a[mid]) {
            return mid;
        } else if (x < a[mid]) {
            right = mid;
        } else {
            left = mid+1;
        }
    }
}

int_fast32_t linear_search(const vector<int_fast32_t> &a, int_fast32_t x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x) return i;
    }
    return -1;
}

void test_solution() {
    srand(1234);

    size_t i, j, l;
    int_fast32_t n, k, r;

    for(j = 0; j < N_ITER; ++j) {
        n = (rand() % KN_MAX + 1 - KN_MIN) + KN_MIN;
        k = (rand() % KN_MAX + 1 - KN_MIN) + KN_MIN;

        vector<int_fast32_t> a(n), b(k), linear(k), binary(k);

        a[0] = (rand() % AB_MAX + 1 - AB_MIN) + AB_MIN;
        for (i = 0; i < n; ++i) {
            r = (rand() % (AB_MAX + 1 - a[i-1])) + a[i-1];
            if (r > AB_MAX) { break;}
            a[i] = r;
        }
        for (i = 0; i < k; ++i) {
            b[i] = (rand() % AB_MAX + 1 - AB_MIN) + AB_MIN;
        }

        for (i = 0; i < k; ++i) {
            linear[i] = linear_search(a, b[i]);
            binary[i] = binary_search(a, b[i]);
            if (linear[i] != binary[i] && a[linear[i]] != b[i]) {
                std::cout << "[-] Mismatch" << std::endl;
                std::cout << "  Array:";
                for (l = 0; l < n; ++l) {
                    std::cout << " " << a[l];
                }
                std::cout << std::endl << "  Search:";
                for (l = 0; l < k; ++l) {
                    std::cout << " " << b[l];
                }
                std::cout << std::endl << "  Linear:";
                for (l = 0; l < k; ++l) {
                    std::cout << " " << linear[l];
                }
                std::cout << std::endl << "  Binary:";
                for (l = 0; l < k; ++l) {
                    std::cout << " " << binary[l];
                }
                return;
            }
        }
        std::cout << "[+] OK (" << j << ")" << std::endl;
    }
}

int main() {
//    test_solution();
    int_fast32_t n;
    std::cin >> n;
    vector<int_fast32_t> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    int_fast32_t m;
    std::cin >> m;
    vector<int_fast32_t> b(m);
    for (int_fast32_t i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    for (int_fast32_t i = 0; i < m; ++i) {
        //replace with the call to binary_search when implemented
        std::cout << binary_search(a, b[i]) << ' ';
    }
}
