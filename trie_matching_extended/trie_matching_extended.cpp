#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>

#define DEBUG 0

class Trie;
typedef int_fast16_t pos_t;
typedef std::map<char, Trie*> Edges;

class Trie {
private:
    pos_t mLabel;
    pos_t mNodeCount;
    Edges mEdges;

    bool isLeaf() {
        return mEdges.find('$') != mEdges.end();
    }

    void addPattern(std::string pattern) {
        Trie* t = this;
        for (char c : pattern) {
            Edges::iterator it = t->mEdges.find(c);
            if (it == t->mEdges.end()) {
                t->mEdges[c] = new Trie(++mNodeCount);
                it = t->mEdges.find(c);
            }
            t = (*it).second;
        }
        t->mEdges['$'] = new Trie(-1);
    }

public:

    Trie(pos_t root = 0) : mLabel(root), mNodeCount(root) {}

    Trie(std::vector<std::string> patterns, pos_t root = 0) : mLabel(root), mNodeCount(root) {
        for (std::string pattern : patterns) {
            addPattern(pattern);
        }
    }

    bool match(std::string str) {
        Trie* t = this;
        for (size_t i = 0; !t->isLeaf() && i < str.size(); ++i) {
            Edges::iterator it = t->mEdges.find(str[i]);
            if (it == t->mEdges.end()) { break; }
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
            for (const auto &e : t->mEdges) {
                std::cout << t->mLabel << "->" << e.second->mLabel << ":" << e.first << std::endl;
                if (!e.second->mEdges.empty()) {
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

    Trie* t = new Trie(patterns);

    size_t n = text.size();
    for (size_t i = 0; i < text.size(); ++i) {
        std::string subs = substr(text, i, n);
        if (t->match(subs)) { result.push_back(i); }
    }

    return result;
}
#if DEBUG
std::vector<int> test(std::vector<std::string>& patterns, std::string& text){
    std::vector<int> pos;
    for (int i=0; i< text.size();i++){
        for (int j=0; j< patterns.size();j++){
            if ((patterns[j].size()+i-1)< text.size()){
                std::string sub=text.substr(i,patterns[j].size());
                if (sub.compare(patterns[j])==0){
                    pos.push_back(i);
                    break;
                }
            }
        }
    }
    std::sort(pos.begin(),pos.end());
    return pos;
}
#endif

int main (void) {
#if DEBUG
    srand(1234);
    for (size_t k = 0; k < 100; ++k) {
        std::cout << k << std::endl;
        const std::string LETTERS = "ATCG";

        int tSize = (rand() % 10000) + 1;
        std::string t = "";
        for (size_t i = 0; i < tSize; ++i) {
            int c = rand() % 4;
            t += LETTERS[c];
        }

        std::vector<std::string> patterns;
        int n = (rand() % 5000) + 1;
        for (size_t i = 0; i < n; ++i) {
            std::string p = "";
            int pSize = (rand() % 100) + 1;
            for (size_t j = 0; j < pSize; ++j) {
                int c = rand() % 4;
                p += LETTERS[c];
            }
            patterns.push_back(p);
        }
#else
        std::string t;
        std::cin >> t;

        int n;
        std::cin >> n;

        std::vector <std::string> patterns (n);
        for (int i = 0; i < n; i++) {
            std::cin >> patterns[i];
        }
#endif
        std::vector<size_t> ans = solve(t, patterns);
#if DEBUG
    std::vector<size_t> testAns = solve(t, patterns);
    }

    if (ans.size() != testAns.size()) {
            std::cout << "Wrong size: " << ans.size() << " vs " << testAns.size() << std::endl;
    } else {
        for (size_t i = 0; i < ans.size(); ++i) {
            if (ans[i] != testAns[i]) {
                std::cout << "Mismatch at " << i << ": " << ans[i] << " vs " << testAns[i] << std::endl;
                break;
            }
        }
    }
#else
    for (int i = 0; i < (int) ans.size (); i++) {

        std::cout << ans[i];
        if (i + 1 < (int) ans.size ()) {
            std::cout << " ";
        }
        else {
            std::cout << std::endl;
        }
    }
#endif

    return 0;
}
