#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

#define INF std::numeric_limits<double>::infinity()

using std::vector;
using std::string;
using std::pair;

const size_t N_ITER = 1e4;
const size_t N_MIN = 2;
const size_t N_MAX = size_t(1e5);
const int_fast32_t XY_MIN = int_fast32_t(-1e9);
const int_fast32_t XY_MAX = int_fast32_t(1e9);
const clock_t T_MAX = 2*CLOCKS_PER_SEC;

struct RectangularCoord {
    int_fast32_t x;
    int_fast32_t y;

    void print() {
        std::cout << "(" << x << ", " << y << ")";
    }

    int_fast32_t dot(RectangularCoord r) {
        return x * r.x + y * r.y;
    }

    double euclidean(RectangularCoord r) {
        return sqrt((x - r.x) * (x - r.x) + (y - r.y) * (y - r.y));
    }

    bool operator ==(const RectangularCoord& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator <(const RectangularCoord& rhs) const {
        if (x < rhs.x) { return true; }
        if (x == rhs.x && y < rhs.y) { return true; }
        return false;
    }

    bool operator <=(const RectangularCoord& rhs) const {
        if (x <= rhs.x && y > rhs.y) { return true; }
        return false;
    }
};

struct {
    bool operator()(RectangularCoord a, RectangularCoord b) {
        if (a.x < b.x) { return true; }
        if (a.x == b.x && b.y < b.y) { return true; }
        return false;
    }
} x_sort;

struct {
    bool operator()(RectangularCoord a, RectangularCoord b) {
        return a.y < b.y;
    }
} y_sort;

double naive_minimal_distance(vector<RectangularCoord> p) {
    size_t i, j;
    double tmp_dst, min_dst;

    min_dst = INF;
    for (i = 0; i < p.size(); ++i) {
        for (j = i+1; j < p.size(); ++j) {
            tmp_dst = p[i].euclidean(p[j]);
            if (tmp_dst < min_dst) {
                min_dst = tmp_dst;
            }
        }
    }

    return min_dst;
}

inline void split_x(vector<RectangularCoord> X, int_fast32_t l, vector<RectangularCoord> &L,
                    vector<RectangularCoord> &R) {

    size_t i, j, k;
    for (i = 0, j = 0, k = 0; j < L.size(); ++i) {
        if (X[i].x <= l) { L[j++] = X[i]; }
        else { R[k++] = X[i]; }
    }

    for (; k < R.size(); ++i, ++k) {
        R[k] = X[i];
    }
}

inline void split_y(vector<RectangularCoord> Y,
                    vector<RectangularCoord> X,
                    int_fast32_t l,
                    vector<RectangularCoord> &L,
                    vector<RectangularCoord> &R) {
    size_t mid = X.size() >> 1;
    for (size_t i = 0; i < Y.size(); ++i) {
        if (Y[i] < X[mid]) { L.push_back(Y[i]); }
        else { R.push_back(Y[i]); }
    }
}

inline double find_closest_pair(vector<RectangularCoord> P) {

    double dist, min_dist;

    min_dist = INF;
    for (size_t i = 0; i < P.size(); ++i) {
        for (size_t j = i+1; j < P.size(); ++j) {
            dist = P[i].euclidean(P[j]);
            if (dist < min_dist) { min_dist = dist; }
        }
    }

    return min_dist;
}

vector<RectangularCoord> isolate_y(vector<RectangularCoord> Y, int_fast32_t l, double min_dist) {

    vector<RectangularCoord> Y_prime(0);

    for (size_t i = 0; i < Y.size(); ++i) {
        if (Y[i].x >= (double)l - min_dist && Y[i].x <= min_dist + (double)l) {
            Y_prime.push_back(Y[i]);
        }
    }

    return Y_prime;
}

double divide(vector<RectangularCoord> X, vector<RectangularCoord> Y) {

    size_t i, j;
    //write your code here
    double dist, dist_l, dist_r, min_dist;
    if (X.size() <= 3) { return find_closest_pair(X); }

    size_t n = X.size();
    int_fast32_t mid = X.size() >> 1;
    vector<RectangularCoord> X_l(mid), X_r(n-mid);
    vector<RectangularCoord> Y_l, Y_r;

    split_x(X, X[mid].x, X_l, X_r);
    split_y(Y, X, X[mid].x, Y_l, Y_r);

    dist_l = divide(X_l, Y_l);
    dist_r = divide(X_r, Y_r);
    min_dist = std::min(dist_l, dist_r);

    vector<RectangularCoord> Y_prime = isolate_y(Y, X[mid].x, min_dist);

    if (Y_prime.size() > 0) {
        for (i = 0; i < Y_prime.size() - 1; ++i) {
            for (j = i + 1; j < i+7 && j < Y_prime.size(); ++j) {
                dist = Y_prime[i].euclidean(Y_prime[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
    }

    return min_dist;
}

double fast_minimal_distance(vector<RectangularCoord> &X) {

    vector<RectangularCoord> Y = X;
    std::sort(X.begin(), X.end(), x_sort);
    std::sort(Y.begin(), Y.end(), y_sort);

    return divide(X, Y);
}

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

int main() {

//    test_solution();
//    test_timing();
    size_t n;
    std::cin >> n;
    vector<RectangularCoord> P(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> P[i].x >> P[i].y;
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << fast_minimal_distance(P) << std::endl;
}
