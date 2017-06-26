#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>

#define DEBUG 0

using std::vector;
using std::pair;

typedef double dist_t;
typedef int_fast8_t data_t;
typedef int_fast16_t coord_t;

template <typename T>
struct Set {
    Set* root_;
    T id_;
    data_t rank_;
#if DEBUG
    char cluster_;
    Set(T id, char cluster = 'A') : id_(id), cluster_(cluster), root_(this), rank_(0) {}
#else
    Set(T id) : id_(id), root_(this), rank_(0) {}
#endif
};

template <typename T>
Set<T>* find(Set<T>* r) {
    std::stack<Set<T>*> chain;
    while(r->root_ != r) {
        chain.push(r);
        r = r->root_;
    }
    while(!chain.empty()) {
        Set<T>* s = chain.top();
        chain.pop();
        s->root_ = r;
    }

    return r;
}

template <typename T>
void merge(Set<T>* i, Set<T>* j) {
    Set<T>* i_id = find(i);
    Set<T>* j_id = find(j);

    if (i_id == j_id) { return; }
    else if (i_id->rank_ > j_id->rank_) {
        j_id->root_ = i_id;
    } else {
        i_id->root_ = j_id;
        if (i_id->rank_ == j_id->rank_) {
            ++j_id->rank_;
        }
    }
}

struct Point;
struct Edge {
    Set<Point*>* start_;
    Set<Point*>* end_;
    dist_t euclidean_;

    Edge(Set<Point*>* start, Set<Point*>* end, dist_t dist) :
            start_(start),
            end_(end),
            euclidean_(dist) {}

    bool operator <(const Edge &rhs) const {
        return euclidean_ < rhs.euclidean_;
    }
};

struct Point {
    coord_t x_;
    coord_t y_;

    Point(coord_t x, coord_t y) : x_(x), y_(y) {}

    dist_t euclidean(Point* p) {
        dist_t x_diff = (dist_t) (x_ - p->x_);
        dist_t y_diff = (dist_t) (y_ - p->y_);
        return sqrt(x_diff * x_diff + y_diff * y_diff);
    }

    std::string toString() {
        return "(" +  std::to_string(x_) + "," + std::to_string(y_) + ")";
    }
};

dist_t clustering(vector<Set<Point*>*> &points, size_t k) {
    vector<Edge> distances;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i+1; j < points.size(); ++j) {
            dist_t dist = points[i]->id_->euclidean(points[j]->id_);
            distances.push_back(Edge(points[i], points[j], dist));
        }
    }

    std::sort(distances.begin(), distances.end());
    std::priority_queue<Edge> paths;
    for (Edge e : distances) {
        Set<Point*>* u = e.start_;
        Set<Point*>* v = e.end_;
        if (find(u) != find(v)) {
            paths.push(e);
            merge(u, v);
        }
    }

    dist_t result;
    for (size_t i = 0; i < k-1; ++i) {
        result = paths.top().euclidean_;
        paths.pop();
    }

    return result;
}

int main() {
#if DEBUG
    size_t n = 12;
    size_t k = 3;
    vector<int> inputs = {
            7, 6,
            4, 3,
            5, 1,
            1, 7,
            2, 7,
            5, 7,
            3, 3,
            7, 8,
            2, 8,
            4, 4,
            6, 7,
            2, 6
    };

    vector<Set<Point*>*> points(n);
    for (size_t i = 0; i < n; ++i) {
        coord_t x = inputs[2*i];
        coord_t y = inputs[2*i + 1];
        points[i] = new Set<Point*>(new Point(x, y));
    }

    std::cout << std::setprecision(10) << clustering(points, k) << std::endl;
#else
    size_t n;
    int k;
    std::cin >> n;
    coord_t x, y;
    vector<Set<Point*>*> points(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x >> y;
        points[i] = new Set<Point*>(new Point(x, y));
    }

    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(points, k) << std::endl;
#endif
}
