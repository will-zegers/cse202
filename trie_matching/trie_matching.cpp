#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <map>
#include <stack>
#include <stdint-gcc.h>

struct Trie;
typedef int_fast16_t pos_t;
typedef std::map<char, Trie*> Edges;

struct Trie {
    pos_t root_;
    pos_t k_;
    Edges edges_;

    Trie(pos_t root = 0) : root_(root), k_(root){}

    bool isLeaf() {
        return edges_.empty();
    }

    void addPattern(std::string pattern) {
        Trie* t = this;
        for (char c : pattern) {
            Edges::iterator it = t->edges_.find(c);
            if (it == t->edges_.end()) {
                t->edges_[c] = new Trie(++k_);
                it = t->edges_.find(c);
            }
            t = (*it).second;
        }
    }

    bool match(std::string str) {
        Trie* t = this;
        for (size_t i = 0; !t->isLeaf(), i < str.size(); ++i) {
            Edges::iterator it = t->edges_.find(str[i]);
            if (it == t->edges_.end()) { break; }
            else {
                t = (*it).second;
            }
        }

        return t->isLeaf();
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

std::string substr(std::string str, size_t begin, size_t end) {
    std::string s = "";

    for (size_t i = begin; i < end; ++i) { s += str[i]; }

    return s;
}

std::vector <size_t> solve (const std::string& text, const std::vector <std::string>& patterns)
{
	std::vector <size_t> result;

    Trie* t = new Trie();
	for (std::string pattern : patterns) {
        t->addPattern(pattern);
    }

    size_t n = text.size();
    for (size_t i = 0; i < text.size(); ++i) {
        std::string subs = substr(text, i, n);
        if (t->match(subs)) { result.push_back(i); }
    }

	return result;
}

int main (void)
{
	std::string t;
	std::cin >> t;

	int n;
	std::cin >> n;

	std::vector <std::string> patterns (n);
	for (int i = 0; i < n; i++) {
		std::cin >> patterns[i];
	}


	std::vector<size_t> ans = solve (t, patterns);

    if (ans.empty()) { std::cout << " " << std::endl; }
    else {
        for (size_t i = 0; i < ans.size(); ++i) {
            std::cout << ans[i] << " ";
        }
        std::cout << std::endl;
    }

	return 0;
}
