#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

typedef int_fast64_t data_t;

static const data_t INF = std::numeric_limits<data_t>::max()>>1;

struct Vertex;
struct Edge {
    Vertex* v_;
    data_t w_;

    Edge(Vertex* v, data_t w) : v_(v), w_(w) {}
};

struct Vertex  {
    data_t key_;
    data_t dist_;
    bool visited_;
    vector<Edge> adj_;

    Vertex() : dist_(INF), key_(0) {}
    Vertex(data_t k) : dist_(INF), key_(k) {}

    bool shortest() {
        return dist_ > -INF;
    }

    bool reachable() {
        return dist_ < INF;
    }
};

inline std::queue<Vertex*> relaxEdges(vector<Vertex *> G) {

    std::queue<Vertex*> Q;

    for (Vertex* u : G) {
        if (u->reachable()) {
            for (Edge e : u->adj_) {
                Vertex *v = e.v_;
                data_t dist = u->dist_ + e.w_;
                if (v->dist_ > dist) {
                    v->dist_ = dist;
                    Q.push(v);
                }
            }
        }
    }

    return Q;
}

void BFS(std::queue<Vertex*> Q) {
    while(!Q.empty()) {
        Vertex* u = Q.front();
        Q.pop();

        u->dist_ = -INF;
        u->visited_ = true;
        for (Edge e : u->adj_) {
            Vertex *v = e.v_;
            if (!v->visited_) {
                Q.push(v);
            }
        }
    }
}


void shortest_paths(vector<Vertex*> G, Vertex* s) {

    s->dist_ = 0;

    std::queue<Vertex*> Q;
    for (size_t i = 0; i < G.size() - 1; ++i) {
        Q = relaxEdges(G);
        if (Q.empty()) { break; }
    }

    if (!Q.empty()) {
        Q = relaxEdges(G);
    }

    if (!Q.empty()) { BFS(Q); }
}

int main() {
    int n, m, s;
    std::cin >> n >> m;

    vector<Vertex*> G(n);
    for (size_t i = 0; i < G.size(); ++i) {
        G[i] = new Vertex(i+1);
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        G[x-1]->adj_.push_back(Edge(G[y-1], w));
    }
    std::cin >> s;
    s--;

    shortest_paths(G, G[s]);
    for (Vertex* V : G) {
        if (!V->reachable()) {
            std::cout << "*\n";
        } else if (!V->shortest()) {
            std::cout << "-\n";
        } else {
            std::cout << V->dist_ << "\n";
        }
    }
}
