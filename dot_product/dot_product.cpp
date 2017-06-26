#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

const uint16_t N_MIN = uint32_t(1);
const uint16_t N_MAX = uint32_t(1e1);
const uint32_t AB_MIN = uint32_t(-1e1);
const uint32_t AB_MAX = uint32_t(1e1);


int64_t max_dot_product(vector<int32_t> a, vector<int32_t> b) {

    size_t i;

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int64_t result = 0;
    for (i = 0; i < a.size(); i++) {
        result += ((int64_t) a[i]) * b[i];
    }
    return result;
}

int main() {
    srand(1234);
    size_t n;
    std::cin >> n;
//    n = 5;
    vector<int32_t> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
//        a[i] = (rand() % (2*AB_MAX)) - AB_MAX;
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
//        b[i] = (rand() % (2*AB_MAX)) - AB_MAX;
    }
    std::cout << max_dot_product(a, b) << std::endl;
}
