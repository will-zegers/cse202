#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;

typedef int_fast16_t coord_t;
typedef double dist_t;

struct Point;
struct Edge {
    Point* startpoint_;
    Point* endpoint_;
    dist_t dist_;

    Edge(Point* p1, Point* p2, dist_t dist) :
            startpoint_(p1),
            endpoint_(p2),
            dist_(dist) {}

    bool operator <(const Edge &rhs) const {
        return dist_ > rhs.dist_;
    }
};

struct Point {
    coord_t x_;
    coord_t y_;
    bool visited_;

    Point() : visited_(false) {}

    dist_t euclidean(Point* p) {
        dist_t x_diff = (dist_t) (x_ - p->x_);
        dist_t y_diff = (dist_t) (y_ - p->y_);
        return sqrt(x_diff * x_diff + y_diff * y_diff);
    }
};

dist_t minimum_distance(vector<Point*> points) {
    dist_t result = 0.;

    std::priority_queue<Edge> nearest;

    Point* current_p = points[0];
    for (size_t i = 0; i < points.size()-1; ++i) {
        current_p->visited_ = true;
        for (size_t j = 0; j < points.size(); ++j) {
            if (!points[j]->visited_) {
                nearest.push(Edge(current_p, points[j], current_p->euclidean(points[j])));
            }
        }
        Edge e = nearest.top();
        nearest.pop();
        while(e.endpoint_->visited_) {
            e = nearest.top();
            nearest.pop();
        }
        result += e.dist_;
        current_p = e.endpoint_;
    }

    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<Point*> points(n);
    for (size_t i = 0; i < points.size(); ++i) {
        points[i] = new Point();
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> points[i]->x_ >> points[i]->y_;
    }
    std::cout << std::setprecision(10) << minimum_distance(points) << std::endl;
}
