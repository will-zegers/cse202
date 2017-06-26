#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;

typedef int_fast32_t data_t;
#define INF std::numeric_limits<data_t>::max()

typedef bool Color;
#define WHITE true
#define BLACK false

struct Vertex {
    data_t idx_;
    data_t dist_;
    Color color_;
    vector<Vertex*> adj_;

    Vertex(data_t idx = 0) : idx_(idx),
                             dist_(INF) {}
};

data_t BFS(vector<Vertex> &G) {

    std::queue<Vertex*> Q;

    G[1].dist_ = 0;
    G[1].color_ = WHITE;
    Q.push(&G[1]);
    while (!Q.empty()) {
        Vertex* u = Q.front();
        Q.pop();
        for (size_t i = 0; i < u->adj_.size(); ++i) {
            Vertex *v = u->adj_[i];
            if (v->dist_ == INF) {
                Q.push(v);
                v->dist_ = u->dist_ + 1;
                v->color_ = !u->color_;
            } else if (u->color_ == v->color_) { return 0; }
        }
    }

    return 1;
}

int main() {
    data_t n, m;
    std::cin >> n >> m;
    vector<Vertex> G(n+1);
    for (size_t i = 0; i < G.size(); ++i) {
        G[i].idx_ = i;
    }

    for (data_t i = 0; i < m; i++) {
        data_t x, y;
        std::cin >> x >> y;
        G[x].adj_.push_back(&G[y]);
        G[y].adj_.push_back(&G[x]);
    }
  std::cout << BFS(G);
}
