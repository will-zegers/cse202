#include <ios>
#include <iostream>
#include <vector>

#define DEBUG 0

#define RED   0x0004
#define GREEN 0x0002
#define BLUE  0x0001

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    std::vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        std::cout << 5*edges.size() << " " <<  3 * numVertices+2 <<  std::endl;
        for (size_t i = 0; i < edges.size(); ++i) {
            std::cout <<  3*edges[i].from << " " << 3*edges[i].from+1 << " " << 3*edges[i].from+2 <<" 0" << std::endl;
            std::cout <<  3*edges[i].to << " " << 3*edges[i].to+1 << " " << 3*edges[i].to+2 <<" 0" << std::endl;
            std::cout << "-" <<  3*edges[i].from << " -" << 3*edges[i].to << " 0" << std::endl;
            std::cout << "-" <<  3*edges[i].from + 1 << " -" << 3*edges[i].to + 1 << " 0" << std::endl;
            std::cout << "-" <<  3*edges[i].from + 2 << " -" << 3*edges[i].to + 2 << " 0" << std::endl;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
#if DEBUG
    n = 3; m = 3;
    std::vector<int> input {
            1,2,2,3,1,3
    };
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (size_t i = 0; i < m; ++i) {
        converter.edges[i].from = input[2*i];
        converter.edges[i].to = input[1+2*i];
    }
#else
    std::cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        std::cin >> converter.edges[i].from >> converter.edges[i].to;
    }
#endif
    converter.printEquisatisfiableSatFormula();

    return 0;
}
