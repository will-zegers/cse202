#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

typedef int_fast32_t data_t;

void getSource(vector<vector<data_t> > &adj_r, vector<data_t> &order, vector<bool> &used, data_t x) {
    for (data_t i = 0; i < adj_r[x].size(); ++i) {
        data_t dest = adj_r[x][i];
        if (!used[dest]) {
            getSource(adj_r, order, used, dest);
        }
    }
    used[x] = true;
    order.push_back(x);
}

vector<data_t> toposort(vector<vector<data_t> > adj, vector<vector<data_t> > adj_r) {

    vector<bool> used(adj_r.size(), false);
    vector<data_t> order;
    //write your code here
    for (data_t i = 1; i < adj_r.size(); ++i) {
        if (!used[i]) {
            getSource(adj_r, order, used, i);
        }
    }
    return order;
}

int main() {
    data_t n, m;
    std::cin >> n >> m;
    vector<vector<data_t> > adj(n+1, vector<data_t>());
    vector<vector<data_t> > adj_r(n+1, vector<data_t>());
    for (data_t i = 0; i < m; i++) {
        data_t x, y;
        std::cin >> x >> y;
        adj[x].push_back(y);
        adj_r[y].push_back(x);
    }
    vector<data_t> order = toposort(adj, adj_r);
    for (data_t i = 0; i < order.size(); i++) {
        std::cout << order[i] << " ";
    }
}
