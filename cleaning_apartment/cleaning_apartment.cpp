#include <bits/stdc++.h>
#include <sstream>

#define DEBUG 0

struct Edge {
    int from;
    int to;

    Edge(int from, int to) : from(from), to(to) {}
};

struct ConvertHampathToSat {
    int numVertices;
    int edgesCount;
    std::vector<std::vector<bool> > edges;

    ConvertHampathToSat(int n, int m) :
            numVertices(n),
            edges(n),
            edgesCount(m) {
        for (size_t i = 0; i < n; ++i) {
            edges[i].resize(n);
        }
    }

    void printEquisatisfiableSatFormula() {

        std::stringstream ss(std::ios_base::app | std::ios_base::in | std::ios_base::out);

        int clauses = 0;
        for (size_t j = 0; j < numVertices; ++j) {
            for (size_t i = 0; i < numVertices * numVertices; i += numVertices) {
                ss << i + j + 1 << " ";
            }
            ss << "0" << std::endl;
            ++clauses;
        }

        for (size_t j = 0; j < numVertices; ++j) {
            for (size_t i = 0; i < numVertices*numVertices; i += numVertices) {
                for (size_t k = i+numVertices; k < numVertices*numVertices; k += numVertices) {
                    ss << "-" << i+j+1 << " -" << k+j+1 << " 0" << std::endl;
                    ++clauses;
                }
            }
        }

        for (size_t i = 0; i < numVertices * numVertices; i += numVertices) {
            for (size_t j = 0; j < numVertices; ++j) {
                ss << i+j+1 << " ";
            }
            ss << "0" << std::endl;
            ++clauses;
        }

        for (size_t i = 0; i < numVertices*numVertices; i += numVertices) {
            for (size_t j = 0; j < numVertices; ++j) {
                for (size_t k = j+1; k < numVertices; ++k) {
                    ss << "-" << i+j+1 << " -" << i+k+1 << " 0" << std::endl;
                    ++clauses;
                }
            }
        }

        for (size_t k = 0; k < numVertices-1; ++k) {
            for (size_t i = 0; i < numVertices; ++i) {
                for (size_t j = 0; j < numVertices; ++j) {
                    if (!edges[i][j] && i != j) {
                        ss << "-" << numVertices*k + i + 1 << " -" << numVertices*(k+1) + j + 1 << " 0" << std::endl;
                        ++clauses;
                    }
                }
            }
        }
        std::cout << clauses << " " << numVertices*numVertices << std::endl;
        std::cout << ss.str();
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
#if DEBUG
    n = 4; m = 3;
    std::vector<int> input {
            1,2,1,3,1,4
    };
#else
    std::cin >> n >> m;
#endif
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        int from, to;
#if DEBUG
        from = input[2*i];
        to = input[2*i+1];
#else
        std::cin >> from >> to;
#endif
        converter.edges[from-1][to-1] = true;
        converter.edges[to-1][from-1] = true;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
