#include <iostream>
#include <vector>
#include <cmath>

const uint32_t ITER = uint32_t(1e6);
const uint32_t N_MIN = uint32_t(1);
const uint32_t N_MAX = uint32_t(1e1);
const uint32_t W_MAX = uint32_t(2e6);
const uint32_t WEIGHTS_MAX = uint32_t(2e6);
const uint32_t VALUES_MAX = uint32_t(2e6);
const uint64_t OUTPUT_MAX = VALUES_MAX * N_MAX;

using std::vector;

inline uint_fast16_t get_max_index(vector<int_fast64_t> w, vector<int_fast64_t> v) {
    int_fast16_t i, n, max_idx;

    double max_a, a;

    max_a = -1;
    max_idx = -1;
    n = w.size();
    for (i = 0; i < n; ++i) {
        a = (w[i] != 0) ? (double)v[i] / w[i] : -1;
        if (a > max_a) {
            max_a = a;
            max_idx = i;
        }
    }

    return max_idx;
}

double get_optimal_value(int_fast32_t capacity, vector<int_fast64_t> &weights, vector<int_fast64_t> &values) {
    int_fast16_t i, j, n;
    double a;
    double value = 0.0;

    n = weights.size();
    i = n - 1;
    while (capacity > 0 && i >= 0) {
        j = get_max_index(weights, values);
        if (j < 0) {
            break;
        }
        a = (weights[j] < capacity) ? (double)weights[j] : (double)capacity;
        value += a * values[j] / weights[j];
        capacity -= a;
        weights[j] -= a;
        --i;
    }

    return value;
}

void test_solution() {
    srand(1234);

    uint_fast16_t i, j, n;
    int_fast32_t capacity;
    uint_fast64_t out;

    for (i = 0; i < ITER; ++i) {

        n = (rand() % N_MAX) + N_MIN;
        capacity = rand() % (W_MAX + 1);

        vector<int_fast64_t> w(n);
        vector<int_fast64_t> v(n);

        for (j = 0; j < n; ++j) {
            w[j] = rand() % (WEIGHTS_MAX + 1);
            v[j] = rand() % (VALUES_MAX + 1);
        }

        out = get_optimal_value(capacity, w, v);

        if(out >= 0 && out <= OUTPUT_MAX && !std::isinf(out)) {
            std::cout << "[+] OK (" << i << ")" << std::endl;
        } else {
            std::cout << "[-] Error: " << std::endl;
            std::cout << "  n: " << n << std::endl;
            std::cout << "  W: " << capacity << std::endl;
            std::cout << "  weights:";
            for (j = 0; j < n; ++j) {
                std::cout << " " << w[j];
            }
            std::cout << std::endl;
            std::cout << "    values:";
            for (j = 0; j < n; ++j) {
                std::cout << " " << v[j];
            }
            std::cout << std::endl;
            std::cout << "  out: " << out << std::endl;
            break;
        }
    }
    std::cout << " Done!" << std::endl;

}

int main() {

//    test_solution();

    uint_fast16_t n;
    int_fast32_t capacity;

    std::cin >> n >> capacity;
    vector<int_fast64_t> weights(n);
    vector<int_fast64_t> values(n);

    for (uint_fast16_t i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }
    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}
