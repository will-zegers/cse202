#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stack>

using std::map;
using std::vector;
using std::string;

struct Trie;
typedef int_fast16_t pos_t;
typedef map<char, Trie*> edge;

struct Trie {
    pos_t root_;
    pos_t k_;
    map<char, Trie*> edges_;

    Trie(pos_t root = 0) : root_(root), k_(root){}

    bool isLeaf() {
        return edges_.empty();
    }

    void addPattern(string pattern) {
        Trie* t = this;
        for (char c : pattern) {
            edge::iterator it = t->edges_.find(c);
            if (it == t->edges_.end()) {
                t->edges_[c] = new Trie(++k_);
                it = t->edges_.find(c);
            }
            t = (*it).second;
        }
    }

    void print() {

        std::stack<Trie*> s;

        s.push(this);
        while (!s.empty()) {
            Trie* t = s.top();
            s.pop();
            for (const auto &e : t->edges_) {
                std::cout << t->root_ << "->" << e.second->root_ << ":" << e.first << std::endl;
                if (!e.second->edges_.empty()) {
                    s.push(e.second);
                }
            }
        }
    }
};

Trie* build_trie(vector<string> & patterns) {
    Trie* root = new Trie();

    for (string pattern : patterns) {
        root->addPattern(pattern);
    }

    return root;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<string> patterns;
    for (size_t i = 0; i < n; i++) {
        string s;
        std::cin >> s;
        patterns.push_back(s);
    }

    Trie* t = build_trie(patterns);
    t->print();

    return 0;
}