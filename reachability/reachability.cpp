#include <iostream>
#include <vector>
#include <stack>

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

int reach(vector<vector<int> > &adj, int x, int y) {
    //write your code here

    vector<bool> visited(adj.size()+1);
    explore(adj, x, visited);

    return visited[y];
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
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x, y);
}
