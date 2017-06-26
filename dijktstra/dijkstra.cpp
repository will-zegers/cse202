#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cassert>

#define DEBUG     0
#define RANDOMIZE 0

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

typedef int_fast32_t data_t;

const data_t INF = std::numeric_limits<data_t>::max()>>1;

struct Edge;
struct Vertex {
    data_t key_;
    data_t dist_;
    vector<Edge> adj_;

    Vertex(data_t k = 0) : key_(k), dist_(INF) {}
};

struct Edge {
    Vertex* v_;
    data_t w_;

    Edge(Vertex* to, data_t cost) : v_(to), w_(cost) {}
};

struct VertexPriority {
    bool operator ()(const Vertex* lhs, const Vertex* rhs) const {
        return lhs->dist_ > rhs->dist_;
    }
};

#if DEBUG
    const size_t N_ITER = 1;

    const size_t MIN_N = 1;
    const size_t MAX_N = size_t(1e1);
    const size_t MIN_M = 0;
    const size_t MAX_M = size_t(2e1);

    const data_t MIN_W = 0;
    const data_t MAX_W = data_t(1e2);

struct InputEdge {
    size_t u_;
    size_t v_;
    size_t w_;

    InputEdge(size_t u, size_t v, size_t w) : u_(u), v_(v), w_(w) {}
};

struct Input {
    size_t n_;
    size_t s_;
    size_t t_;
    vector<InputEdge> edges_;

    size_t m() { return edges_.size(); }
    Input(size_t n, size_t s, size_t t) : n_(n), s_(s), t_(t) {}
};

void print_graph(vector<Vertex> V) {
    for (size_t i = 0; i < V.size(); ++i) {
        std::cout << V[i].key_ << ":" << std::endl;
        std::cout << "\tdist: " << V[i].dist_ << std::endl;
        std::cout << "\tadj: ";
        for (Edge e : V[i].adj_) {
             std::cout << e.v_->key_ << " " << e.w_<< " ";
        }
        std::cout << std::endl;
    }
}

void test1(vector<Vertex> G) {
    const data_t MAX = std::numeric_limits<data_t>::max();
    for (Vertex v : G) {
        assert(v.dist_ == MAX);
    }
    std::cout << "PASS" << std::endl;
}
#endif

data_t distance(vector<Vertex*> G, size_t s, size_t t) {

    G[s]->dist_ = 0;

    std::priority_queue<Vertex*, std::vector<Vertex*>, VertexPriority> H;
    for (Vertex* v : G) {
        H.push(v);
    }
    while (!H.empty()) {
        Vertex* u = H.top();
        H.pop();
        for (Edge e : u->adj_) {
            Vertex *v = e.v_;
            data_t dist = u->dist_ + e.w_;
            if (v->dist_ > dist) {
                v->dist_ = dist;
                H.push(v);
            }
        }
    }

    return (G[t]->dist_ == INF) ? -1 : G[t]->dist_;
}

#if DEBUG
int main() {
#if RANDOMIZE
    size_t n = (random() % (MAX_N + 1 - MIN_N)) + MIN_N;
    size_t m = (random() % (MAX_M + 1 - MIN_M)) + MIN_M;

    size_t s = (random() % (n + 1 - MIN_N)) + MIN_N;
    size_t t = (random() % (n + 1 - MIN_N)) + MIN_N;
    Input ipt(n, s, t);

    for (size_t i = 0; i < m; ++i) {
        size_t u = (random() % (n + 1 - MIN_N)) + MIN_N;
        size_t v = (random() % (n + 1 - MIN_N)) + MIN_N;
        data_t w = (rand() % (MAX_W + 1 - MIN_W)) + MIN_W;
        ipt.edges_.push_back(InputEdge(u,v,w));
    }
#else
    Input ipt(5, 1, 5);
    ipt.edges_.push_back(InputEdge(1,2,4));
    ipt.edges_.push_back(InputEdge(1,3,2));
    ipt.edges_.push_back(InputEdge(2,3,2));
    ipt.edges_.push_back(InputEdge(3,2,1));
    ipt.edges_.push_back(InputEdge(2,4,2));
    ipt.edges_.push_back(InputEdge(3,5,4));
    ipt.edges_.push_back(InputEdge(5,4,1));
    ipt.edges_.push_back(InputEdge(2,5,3));
    ipt.edges_.push_back(InputEdge(3,4,4));
#endif

    vector<Vertex*> G(ipt.n_);
    for (size_t i = 0; i < G.size(); ++i) {
        G[i] = new Vertex();
    }
    for (InputEdge i : ipt.edges_) {
        G[i.u_-1]->adj_.push_back(Edge(G[i.v_-1], i.w_));
    }

    std::cout << distance(G, --ipt.s_, --ipt.t_) << std::endl;
}
#else
int main() {
    size_t n, m;
    std::cin >> n >> m;

    vector<Vertex*> G(n+1);
    for (size_t i = 0; i < G.size(); ++i) {
        G[i] = new Vertex();
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        G[x-1]->adj_.push_back(Edge(G[y-1], w));
    }
    size_t s, t;
    std::cin >> s >> t;
    std::cout << distance(G, --s, --t);
}
#endif