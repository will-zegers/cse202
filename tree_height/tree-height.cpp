#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#include <queue>

#endif

#define DEBUG 0

typedef int32_t data_t;

#if DEBUG

#define v1dump(v) { \
    for (size_t i = 0; i < v.size(); ++i) { \
        std::cout << v[i].key << " "; \
    } \
    std::cout << std::endl; \
}

const int SEED      = 1237;
const data_t N_ITER = data_t(1e0);
const data_t N_MIN  = 1;
const data_t N_MAX  = data_t(1e1);
const time_t T_MAX  = 2 * 1000;
#endif

class Node;

class Node {
public:
    data_t key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }

    bool hasChildren() {
        return children.size() > 0;
    }

    bool hasCycle() {
        Node *current_parent = parent;
        while (parent != NULL) {
            if (current_parent == this) {
                return true;
            }
            current_parent = (*current_parent).parent;
        }
    }
};

void fast_get_height(std::vector<Node> &nodes, std::vector<data_t> &depths, data_t r_idx) {

    for (data_t i = 0; i < nodes[r_idx].children.size(); ++i) {
        data_t child_key = (*nodes[r_idx].children[i]).key;
        depths[child_key] = depths[r_idx] + 1;
        fast_get_height(nodes, depths, child_key);
    }
}

data_t naive_get_height(std::vector<Node> nodes) {

    data_t maxHeight = 0;
    for (data_t leaf_index = 0; leaf_index < nodes.size(); leaf_index++) {
        data_t height = 0;
        for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent) {
            height++;
        }
        maxHeight = std::max(maxHeight, height);
    }

    return maxHeight;
}

#if DEBUG
data_t main_with_large_stack_space() {
    srand(SEED);

    for (data_t i = 0; i < N_ITER; ++i) {
        data_t n = (rand() % (N_MAX - 1 + N_MIN)) + N_MIN;
        data_t root_index = rand() % n;

        std::vector<Node> nodes(n);
        for (data_t child_index = 0; child_index < n; child_index++) {
            data_t parent_index = (child_index == root_index) ? -1 : rand() % n;
            if (parent_index >= 0) {
                nodes[child_index].setParent(&nodes[parent_index]);
            }
            nodes[child_index].key = child_index;
        }

        data_t naive = naive_get_height(nodes);
        data_t fast = fast_get_height(nodes, root_index);
        if (fast != naive) {
            std::cout << "[-] Error: " << std::endl;
            std::cout << "  Input: ";
            for (size_t j = 0; j < parents.size(); ++j) {
                std::cout << parents[j] << " ";
            }
            std::cout << std::endl;
            std::cout << "  Naive: " << naive << std::endl;
            std::cout << "  Fast: " << fast << std::endl;
            return 0;
        }
        std::cout << "[+] OK (" << i << ")" << std::endl;
    }
    return 0;
}
#else
data_t main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(0);
    data_t n;
    data_t root_index = -1;
    std::cin >> n;

    std::vector<Node> nodes(n);
    std::vector<data_t> depths(n,1);
    for (data_t child_index = 0; child_index < n; child_index++) {
        data_t parent_index;
        std::cin >> parent_index;

        if (parent_index >= 0) {
            nodes[child_index].setParent(&nodes[parent_index]);
        } else {
            root_index = child_index;
        }
        nodes[child_index].key = child_index;
    }

    data_t maxHeight = 0;
    fast_get_height(nodes, depths, root_index);
    for (size_t i = 0; i < depths.size(); ++i) {
        maxHeight = std::max(maxHeight, depths[i]);
    }
    std::cout << maxHeight << std::endl;
    return 0;
}
#endif

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    data_t result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }

#endif
    return main_with_large_stack_space();
}
