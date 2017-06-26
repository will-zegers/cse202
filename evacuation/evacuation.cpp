#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef int flow_t;

struct Edge {
    size_t from_;
    size_t to_;
    flow_t capacity_;
    flow_t flow_;

    Edge(size_t from, size_t to, flow_t capacity) :
            from_(from),
            to_(to),
            capacity_(capacity),
            flow_(0) {}
#endif


    void updateEdge(flow_t delta) {
        flow_ += delta;
        capacity_ -= delta;
    }

    inline bool isSaturated() {
        return capacity_ == 0;
    }

    inline bool isLoop() {
        return to_ == from_ || to_ == 0;
    }
};

typedef std::vector<size_t> Path;
class FlowNetwork {
private:
    std::vector<std::vector<size_t> > mNodes;

    void inputEdges(size_t m, size_t n) {
        mNodes.resize(n);
        for (size_t i = 0; i < m; ++i) {
            size_t from, to;
            flow_t cap;
            std::cin >> from >> to >> cap;

            Edge* forward_edge = new Edge(from-1, to-1, cap);
            Edge* backward_edge = new Edge(to-1, from-1, 0);

            mNodes[from-1].push_back(edges.size());
            edges.push_back(forward_edge);
            mNodes[to-1].push_back(edges.size());
            edges.push_back(backward_edge);
        }
    }

public:

    size_t targetNode;
    std::vector<Edge*> edges;

    FlowNetwork(size_t m, size_t n) {
        targetNode = n-1;
        inputEdges(m, n);
    }

    void updateEdges(Path p, flow_t delta) {
        for (size_t i : p) {
            edges[i]->updateEdge(delta);
            edges[i^1]->updateEdge(-delta);
        }
    }

    flow_t getMinCapactiy(Path p) {
        flow_t minCap = std::numeric_limits<flow_t>::max();
        for (size_t e : p) {
            if (edges[e]->capacity_ < minCap) {
                minCap = edges[e]->capacity_;
            }
        }
        return minCap;
    }
};

Path shortestPath(FlowNetwork F) {
    std::queue<Path> Q;

    std::vector<bool> visited(F.targetNode+1);

    for(size_t i : F[0]) {
        for (size_t j = 0; j < 2; ++j) {
            if (F.edges[i^j]->isSaturated() || F.edges[i^j]->isLoop()) {
                continue;
            }
            Path path = {i^j};
            Q.push(path);
        }
    }
    visited[0] = true;

    while(!Q.empty()) {
        Path path = Q.front();
        Q.pop();

        size_t nextNode = F.edges[path.back()]->to_;
        visited[nextNode] = true;
        if (nextNode == F.targetNode) {
            return path;
        }

        for (size_t e : F[nextNode]) {
            for (size_t i = 0; i < 2; ++i) {
                if (visited[F.edges[e^i]->to_] || F.edges[e^i]->isSaturated() || F.edges[e^i]->isLoop()) {
                    continue;
                }

                Path newPath = path;
                newPath.push_back(e^i);
                if (F.edges[e^i]->to_ == F.targetNode) {
                    return newPath;
                }

                Q.push(newPath);
            }
        }
    }

    return {};
}

flow_t max_flow(FlowNetwork F) {

    flow_t maxFlow = 0;

    for(Path p = shortestPath(F); p.size() > 0; p = shortestPath(F)) {
        flow_t flow = F.getMinCapactiy(p);
        F.updateEdges(p, flow);
        maxFlow += flow;
    }

    return maxFlow;
}

int main() {

    size_t m, n;

    std::cin >> n >> m;

    FlowNetwork FN(m, n);
    std::cout << max_flow(FN) << std::endl;
    return 0;
}
