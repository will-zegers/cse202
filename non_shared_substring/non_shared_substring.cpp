#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <cstring>
#include <queue>

#define DEBUG 0

int leafEnd = 0;
int *rootEnd = new int(-1);
int *splitEnd;

std::string text;

struct Node {
    Node *suffixLink_;
    std::map<char, Node *> children_;

    int start_;
    int* end_;

    Node(int start, int* end, Node* sl) : start_(start), end_(end), suffixLink_(sl) {}

    int edgeLength() {
        return *end_ - start_ + 1;
    }

    std::string toString(std::string text) {
        std::string s = "";
        for (int i = start_; i <= *end_; ++i) {
            s += text[i];
        }
        return s;
    }
};

struct ActivePoint {
    Node* node_;
    int edge_;
    int length_;

    ActivePoint(Node* node, char edge, int length) : node_(node), edge_(edge), length_(length) {}
};

struct Path {
    Node *current_;

    std::string sub_;

    Path(Node* current) : current_(current), sub_("") {}
    Path(Node* current, std::string sub) : current_(current) {
        sub_ = sub + current->toString(text);
    }
};

ActivePoint *active;

bool isNonShared(Node* n, size_t hashPos) {

    if (n->start_ > hashPos) {
        return false;
    }
    if (n->children_.empty()) {
        return true;
    }
    for (const auto& c : n->children_) {
        if (!isNonShared(c.second, hashPos)) { return false; }
    }

    return true;
}

bool walkDown(Node *n) {
    if (n->edgeLength() <= active->length_) {
        active->length_ -= n->edgeLength();
        active->edge_ += n->edgeLength();
        active->node_ = n;

        return true;
    }
    return false;
}

void buildTreeFromText(std::string text, Node *root) {

    active = new ActivePoint(root, 0, 0);
    int remainingSuffixCount = 0;

    for (int i = 0; i < text.size(); ++i) {
        leafEnd = i;
        remainingSuffixCount++;

        Node *newNode = NULL;
        while (remainingSuffixCount > 0) {

            if (active->length_ == 0) { active->edge_ = i; }
            std::map<char, Node *>::iterator it = active->node_->children_.find(text[active->edge_]);
            if (it == active->node_->children_.end()) {
                active->node_->children_[text[active->edge_]] = new Node(i, &leafEnd, root);
                if (newNode != NULL) {
                    newNode->suffixLink_ = active->node_;
                    newNode = NULL;
                }
            } else {
                Node *next = it->second;
                if (walkDown(next)) { continue; }
                if (text[next->start_ + active->length_] == text[i]) {
                    if (newNode != NULL && active->node_ != root) {
                        newNode->suffixLink_ = active->node_;
                        newNode = NULL;
                    }

                    ++active->length_;
                    break;
                }
                splitEnd = new int(next->start_ + active->length_ - 1);

                Node *split = new Node(next->start_, splitEnd, root);
                active->node_->children_[text[active->edge_]] = split;

                split->children_[text[i]] = new Node(i, &leafEnd, root);
                next->start_ += active->length_;

                split->children_[text[next->start_]] = next;

                if (newNode != NULL) {
                    newNode->suffixLink_ = split;
                }

                newNode = split;
            }

            --remainingSuffixCount;
            if (active->node_ != root) {
                active->node_ = active->node_->suffixLink_;
            } else if (active->length_ > 0) {
                --active->length_;
                active->edge_ = i - remainingSuffixCount + 1;
            }
        }
    }
}

std::string solve (std::string p, std::string q)
{
    text = p + "#" + q + "$";
    Node *root = new Node(-1, rootEnd, NULL);
    buildTreeFromText(text, root);

    std::queue<Path*> Q;
    Q.push(new Path(root));

    size_t minSize = p.size();
    std::string result = p;
    while(!Q.empty()) {
        Path* ph = Q.front();
        Q.pop();

        for (const auto& n : ph->current_->children_) {
            if (text[n.second->start_] != '#') {
                if (isNonShared(n.second, p.size())) {
                    std::string sub = ph->sub_ + text[n.second->start_];
                    if (sub.size() < minSize) {
                        result = sub;
                        minSize = sub.size();
                    }
                } else {
                    Q.push(new Path(n.second, ph->sub_));
                }
            }
        }
    }

	return result;
}

int main (void)
{
	std::string p;
	std::cin >> p;
	std::string q;
	std::cin >> q;

	std::string ans = solve (p, q);

	std::cout << ans << std::endl;

	return 0;
}
