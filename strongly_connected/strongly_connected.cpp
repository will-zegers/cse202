#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

typedef int_fast32_t data_t;

using std::vector;
using std::pair;

static size_t clk = 1;

struct Vertex {
    data_t idx_;
    size_t post_;
    vector<Vertex*> neighbors_;
    bool visited_;

    Vertex(data_t idx) : idx_(idx),
                         post_(std::numeric_limits<size_t>::max()),
                         neighbors_(vector<Vertex*>(0)),
                         visited_(false) {}

    bool operator <(const Vertex &rhs) const {
        return post_ >= rhs.post_;
    }
};

void explore(Vertex* v) {

    v->visited_ = true;

    for (size_t i = 0; i < v->neighbors_.size(); ++i) {
        Vertex* n = v->neighbors_[i];
        if (!n->visited_) {
            explore(n);
        }
    }
    v->post_ = clk++;
}

void DFS(vector<Vertex> &G) {

    for (size_t i = 1; i < G.size(); ++i) {
        Vertex* v = &G[i];
        if (!v->visited_) {
            explore(v);
        }
    }
}

data_t SCC(vector<Vertex> &G, vector<Vertex> &G_r) {

    DFS(G_r);

    std::sort(G_r.begin(), G_r.end());

    data_t cc = 0;
    for (size_t i = 1; i < G.size(); ++i) {
        data_t idx = G_r[i].idx_;
        Vertex* v = &G[idx];
        if (!v->visited_) {
            ++cc;
            explore(v);
        }
    }

    return cc;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;

    vector<Vertex> G;
    vector<Vertex> G_r;
    for (size_t i = 0; i < n+1; ++i) {
        G.push_back(Vertex(i));
        G_r.push_back(Vertex(i));
    }

    for (size_t i = 0; i < m; i++) {
        data_t x, y;
        std::cin >> x >> y;
        G[x].neighbors_.push_back(&G[y]);
        G_r[y].neighbors_.push_back(&G_r[x]);
    }
    std::cout << SCC(G, G_r);
}
