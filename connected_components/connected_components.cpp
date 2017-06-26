#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector<vector<int> > &adj, int v, vector<bool> &visited) {
    visited[v] = true;
    for (size_t i = 0; i < adj[v].size(); ++i) {
        int dest = adj[v][i];
        if (!visited[dest]) {
            explore(adj, dest, visited);
        }
    }
}

int number_of_components(vector<vector<int> > &adj) {
    int res = 0;

    vector<bool> visited(adj.size()+1);
    for (size_t i = 1; i < adj.size(); ++i) {
        if (!visited[i]) {
            ++res;
            explore(adj, i, visited);
        }
    }
    return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n+1, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    std::cout << number_of_components(adj);
}
