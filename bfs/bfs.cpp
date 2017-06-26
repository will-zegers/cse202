#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;

typedef int_fast32_t data_t;
#define INF std::numeric_limits<data_t>::max()

struct Vertex {
    data_t idx_;
    data_t dist_;
    vector<Vertex*> adj_;

    Vertex(data_t idx = 0) : idx_(idx),
                         dist_(INF) {}
};

data_t distance(vector<Vertex> &G, data_t s, data_t t) {

    std::queue<Vertex*> Q;

    G[s].dist_ = 0;
    Q.push(&G[s]);
    while (!Q.empty()) {
        Vertex* u = Q.front();
        Q.pop();
        for (size_t i = 0; i < u->adj_.size(); ++i) {
            Vertex *v = u->adj_[i];
            if (v->dist_ == INF) {
                Q.push(v);
                v->dist_ = u->dist_ + 1;
            }
        }
    }

    return (G[t].dist_ == INF) ? -1 : G[t].dist_;
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
    data_t s, t;
    std::cin >> s >> t;
    std::cout << distance(G, s, t);
}
