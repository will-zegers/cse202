#include <iostream>
#include <vector>

using std::vector;

const int_fast32_t MAX_N = int_fast32_t(1e9);

//inline bool isInSummands(int_fast32_t a, vector<int_fast32_t> summands, int_fast32_t n) {
//    int_fast32_t i;
//
//    for (i = 0; i < summands.size(); ++i) {
//        if (a == summands[i] || a + summands[i] == n || a + a == n) {
//            return true;
//        }
//    }
//    return false;
//}

vector<int_fast32_t> optimal_summands(int_fast32_t n) {
    int_fast32_t l;
    vector<int_fast32_t> summands;

    for (l = 1; n > 0; ++l) {
        if (2 * l < n) {
            summands.push_back(l);
            n -= l;
        } else {
            summands.push_back(n);
            n -= n;
        }
    }

    return summands;
}

int main() {
    int_fast32_t n;
    std::cin >> n;
    vector<int_fast32_t> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
