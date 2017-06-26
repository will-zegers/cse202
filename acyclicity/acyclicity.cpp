#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool hasCycle(vector<vector<int> > &adj, int v, vector<bool> &visited, vector<bool> &removed) {

    if (visited[v]) { return true; }

    visited[v] = true;
    for (size_t i = 0; i < adj[v].size(); ++i) {
        int dest = adj[v][i];
        if (!removed[dest]) {
            if (hasCycle(adj, dest, visited, removed)) { return true; }
        }
    }

    removed[v] = true;
    return false;
}

int acyclic(vector<vector<int> > &adj) {
    //write your code here

    vector<bool> removed(adj.size(), false);
    for (size_t i = 1; i < adj.size(); ++i) {
        if (!removed[i]) {
            vector<bool> visited(adj.size(), false);
            if (hasCycle(adj, i, visited, removed)) { return true; }
        }
    }
    return false;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n+1, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x].push_back(y);
    }
    std::cout << acyclic(adj);
}
