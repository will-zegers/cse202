#include <stress_test.h>

void test_solution() {
    srand(1234);

    size_t i, j, k, n, z;

    double naive, fast;

    for (i = 0; i < N_ITER; ++i) {
        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<RectangularCoord> P(n), X(n), Y(n);
        for (j =0; j < n; ++j) {
            P[j].x = (rand() % (XY_MAX + 1 - XY_MIN)) + XY_MIN;
            P[j].y = (rand() % (XY_MAX + 1 - XY_MIN)) + XY_MIN;
            X[j].x = P[j].x;
            X[j].y = P[j].y;
            Y[j].x = P[j].x;
            Y[j].y = P[j].y;
        }

        fast = fast_minimal_distance(X);
        naive = naive_minimal_distance(P);

        if (naive != fast || fast > 9999999) {
            std::cout << "[-] Mismatch (" << i << ")" << std::endl;
            std::cout << "  Points: " << std::endl;
            for (k = 0; k < P.size(); ++k){
                std::cout << "    " << P[k].x << " " << P[k].y << std::endl;
            }

            std::cout << "  Naive: " << naive << std::endl;
            std::cout << "  Fast: " << fast << std::endl;
            return;
        }
        std::cout << "[OK] (" << i << ")" << std::endl;
    }
}
//
void test_timing() {
    srand(1234);

    size_t i, j, n;
    clock_t t;
    double fast;

    for (i = 0; i < N_ITER; ++i) {
        n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

        vector<RectangularCoord> P(n), X(n), Y(n);
        for (j =0; j < n; ++j) {
            P[j].x = (rand() % (XY_MAX + 1 - XY_MIN)) + XY_MIN;
            P[j].y = (rand() % (XY_MAX + 1 - XY_MIN)) + XY_MIN;
            X[j].x = P[j].x;
            X[j].y = P[j].y;
            Y[j].x = P[j].x;
            Y[j].y = P[j].y;
        }

        t = clock();
        fast = fast_minimal_distance(X);
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