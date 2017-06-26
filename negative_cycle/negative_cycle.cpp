#include <iostream>
#include <vector>
#include <limits>

using std::vector;

#define DEBUG 1

typedef int_fast64_t data_t;

const data_t INF = std::numeric_limits<data_t>::max()>>1;

struct Vertex;
struct Edge {
    Vertex* v_;
    data_t w_;

    Edge(Vertex* v, data_t w) : v_(v), w_(w) {}
};

struct Vertex  {
    data_t dist_;
    vector<Edge> adj_;

    Vertex() : dist_(INF) {}

#if DEBUG
    data_t key_;
    Vertex(data_t k) : dist_(INF), key_(k) {}
#endif
};

Vertex* nextUnvisitedNode(vector<Vertex*> G) {
    for (Vertex* v : G) {
        if (v->dist_ == INF) { return v; }
    }
    return NULL;
}

inline bool relaxEdges(vector<Vertex*> G) {
    bool hasUpdated = false;
    for (Vertex* u : G) {
        for (Edge e : u->adj_) {
            Vertex* v = e.v_;
            data_t dist = u->dist_+ e.w_;
            if (v->dist_ > dist) {
                v->dist_ = dist;
                hasUpdated = true;
            }
        }
    }

    return hasUpdated;
}

int negative_cycle(vector<Vertex*> G) {

    Vertex* s = G[0];
    while (s != NULL) {
        s->dist_ = 0;
        bool hasChanged = false;
        for (size_t i = 0; i < G.size() - 1; ++i) {
            hasChanged = relaxEdges(G);
            if (!hasChanged) { break; }
        }

        if (hasChanged && relaxEdges(G)) { return 1; }
        s = nextUnvisitedNode(G);
    }

    return 0;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;

    vector<Vertex*> G(n);
    for (size_t i = 0; i < G.size(); ++i) {
        G[i] = new Vertex();
#if DEBUG
        G[i]->key_ = i+1;
#endif
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        G[x-1]->adj_.push_back(Edge(G[y-1], w));
    }
    std::cout << negative_cycle(G);
}
