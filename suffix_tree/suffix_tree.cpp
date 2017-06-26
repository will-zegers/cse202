#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <cstring>

#define DEBUG 0

int leafEnd = 0;
int rootEnd = -1;
int *splitEnd;

struct Node {
    Node *suffixLink_;
    std::map<char, Node *> children_;

    int start_;
    int* end_;

    Node(int start, int* end, Node* sl) : start_(start), end_(end), suffixLink_(sl) {}

    int edgeLength() {
        return *end_ - start_ + 1;
    }
};

struct ActivePoint {
    Node* node_;
    int edge_;
    int length_;

    ActivePoint(Node* node, char edge, int length) : node_(node), edge_(edge), length_(length) {}
};

ActivePoint *active;

bool walkDown(Node *n) {
    if (n->edgeLength() <= active->length_) {
        active->length_ -= n->edgeLength();
        active->edge_ += n->edgeLength();
        active->node_ = n;

        return true;
    }
    return false;
}

#if DEBUG
void printNode(std::string text, Node* node) {

    for (int i = node->start_; i < *(node->end_)+1; ++i) {
        std::cout << text[i];
    }
    std::cout << std::endl;
    for (const auto& n : node->children_) {
        printNode(text, n.second);
    }
}

void printTree(std::string text, Node *root) {
    Node *node = root;
    for (const auto& n : root->children_) {
        printNode(text, n.second);
    }
}
#endif

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

std::vector<std::string> computeSuffixTreeEdges(std::string text) {

    std::vector<std::string> edges;

    Node* root = new Node(-1, &rootEnd, NULL);
    buildTreeFromText(text, root);

    std::stack<Node *> K;

    for (const auto& n : root->children_) {
        K.push(n.second);
    }
    while(!K.empty()) {
        Node *p = K.top();
        K.pop();

        std::string s = "";
        for (int i = p->start_; i < *(p->end_)+1; ++i) {
            s += text[i];
        }
        edges.push_back(s);

        for (const auto& n : p->children_) {
            K.push(n.second);
        }
    }

    return edges;
}


int main() {
    std::string text;
//    std::cin >> text;
    text = "CCAAGCTGCTAGAGG#CATGCTGGGCTGGCT$";
    std::vector<std::string> edges = computeSuffixTreeEdges(text);
    for (int i = 0; i < edges.size(); ++i) {
        std::cout << edges[i] << std::endl;
    }
    return 0;
}