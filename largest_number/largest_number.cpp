#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

const int_fast16_t N_MIN     = 1;
const int_fast16_t N_MAX     = int_fast32_t(1e2);
const int_fast16_t A_MIN     = 1;
const int_fast16_t A_MAX     = int_fast32_t(1e3);
const int_fast16_t TEST_ITER = int_fast32_t(1e6);

struct Number {
    string n;

    bool operator <(const Number& rhs) const {
        uint_fast16_t i;

        return std::stol(n + rhs.n) < std::stol(rhs.n + n);
    }
};

string largest_number_naive(vector<Number> a) {

    string value_str;
    std::stringstream strm;
    long long max_value;
    vector<Number> a_copy = a;

    value_str = "";

    for (size_t i = 0; i < a_copy.size(); ++i) {
        value_str += a[i].n;
    }
    max_value = (long long)stol(value_str);


    while (prev_permutation(a_copy.begin(), a_copy.end())) {
        value_str = "";
        for (size_t i = 0; i < a_copy.size(); ++i) {
            value_str += a_copy[i].n;
        }
        max_value = std::max((long long)stol(value_str), max_value);
    }

    while (next_permutation(a.begin(), a.end())) {
        value_str = "";
        for (size_t i = 0; i < a.size(); ++i) {
            value_str += a[i].n;
        }
        max_value = std::max((long long)stol(value_str), max_value);
    }

    return std::to_string(max_value);
}

string largest_number_fast(vector<Number> a) {

    string result;
    std::stringstream ret;

    std::sort(a.begin(), a.end());

    for (size_t i = 1; i <= a.size(); ++i) {
        ret << a[a.size()-i].n;
    }

    ret >> result;
    return result;
}

void test_solution() {
    srand(1234);
    string fast_sol, naive_sol;
    size_t i, j;

    for (i = 0; i < TEST_ITER; ++i) {

        int_fast32_t n = (rand() % N_MAX) + N_MIN;

        vector<Number> a(n);
        for (size_t i = 0; i < a.size(); ++i) {
            a[i].n = std::to_string((rand() % A_MAX) + A_MIN);
        }

        fast_sol = largest_number_fast(a);
        naive_sol = largest_number_naive(a);

        if (naive_sol.compare(fast_sol) == 0) {
            std::cout << "[+] OK (" << i << ")" << std::endl;
        } else {
            std::cout << "[-] Error" << std::endl;
            std::cout << "  Input: ";
            for (j = 0; j < a.size(); ++j) {
                std::cout << a[j].n << " ";
            }
            std::cout << std::endl;
            std::cout << "  Naive: ";
            std::cout << naive_sol << std::endl;
            std::cout << "  Fast: ";
            std::cout << fast_sol << std::endl;
            break;
        }
    }
    std::cout << "[i] Done!" << std::endl;
}

int main() {
//    test_solution();
    int n;
    std::cin >> n;
    vector<Number> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i].n;
    }
    std::cout << largest_number_fast(a);
}
