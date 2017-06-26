#include <ios>
#include <iostream>
#include <vector>

struct ConvertILPToSat {
    std::vector< std::vector<int> > A;
    std::vector<int> b;

    ConvertILPToSat(int n, int m) : A(n, std::vector<int>(m)), b(n)
    {}

    void printEquisatisfiableSatFormula() {

    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        std::cin >> converter.A[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      std::cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
