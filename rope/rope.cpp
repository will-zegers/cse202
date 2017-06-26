#include <cstdio>
#include <string>
#include <iostream>
#include <limits>
#include <cassert>

#define DEBUG 0

typedef long long int data_t;

const data_t INF = std::numeric_limits<data_t>::max()>>1;

struct Vertex {
    data_t key_;
    char char_;
    data_t size_;
    Vertex* parent_;
    Vertex* left_;
    Vertex* right_;

    Vertex(char letter, Vertex* P = NULL, data_t k = 0) :
            char_(letter),
            key_(k),
            size_(1),
            parent_(P),
            left_(NULL),
            right_(NULL) {}

    void update() {
        size_ = 1;
        if (left_ != NULL) {
            size_ += left_->size_;
        }
        if (right_ != NULL) {
            size_ += right_->size_;
        }
    }
};

class SplayTree {
private:
    Vertex* mRoot;

    void zig(Vertex* N, Vertex* P) {
        if (N->key_ > P->key_) {
            P->right_ = N->left_;
            if (N->left_) { N->left_->parent_ = P; }
            N->left_ = P;
        } else {
            P->left_ = N->right_;
            if (N->right_) { N->right_->parent_ = P; }
            N->right_ = P;
        }
        P->parent_ = N;
        N->parent_ = NULL;
    }

    void zigZig(Vertex* N, Vertex* P, Vertex* Q) {
        if (P->key_ < Q->key_) {
            Q->left_ = P->right_;
            if (P->right_) { P->right_->parent_ = Q; }

            P->left_ = N->right_;
            if (N->right_) { N->right_->parent_ = P; }

            N->right_ = P;
            P->right_ = Q;
        } else {
            Q->right_ = P->left_;
            if (P->left_) { P->left_->parent_ = Q; }

            P->right_ = N->left_;
            if (N->left_) { N->left_->parent_ = P; }

            N->left_ = P;
            P->left_ = Q;
        }
        Q->parent_ = P;
    }

    void zigZag(Vertex* N, Vertex* P, Vertex* Q) {

        if (P->key_ < Q->key_) {
            Q->left_ = N->right_;
            if (N->right_) { N->right_->parent_ = Q;}

            P->right_ = N->left_;
            if (N->left_) { N->left_->parent_ = P; }

            N->left_ = P;
            N->right_ = Q;
        } else {
            Q->right_ = N->left_;
            if (N->left_) { N->left_->parent_ = Q;}

            P->left_ = N->right_;
            if (N->right_) { N->right_->parent_ = P; }

            N->right_ = P;
            N->left_ = Q;
        }
        Q->parent_ = N;
    }

    void splay(Vertex* N) {

        if (N == NULL || N->parent_ == NULL) { return; }

        Vertex* P = N->parent_;
        if(P->parent_ == NULL) {
            zig(N, P);
        } else {
            Vertex *Q = P->parent_;
            Vertex *S = Q->parent_;
            if (N->key_ > P->key_) {
                if (P->key_ > Q->key_) {
                    zigZig(N, P, Q);
                } else {
                    zigZag(N, P, Q);
                }
            } else {
                if (P->key_ > Q->key_) {
                    zigZag(N, P, Q);
                } else {
                    zigZig(N, P, Q);
                }
            }
            if (S != NULL) {
                if (S->key_ > Q->key_) { S->left_ = N; }
                else { S->right_ = N; }
            }

            N->parent_ = S;
            P->parent_ = N;

            Q->update();
        }
        P->update();
        N->update();

        if (N->parent_ != NULL) { splay(N); }
        else {mRoot = N;}
    }

    Vertex* leftDescendant(Vertex* N) {
        return (N->left_ == NULL) ? N : leftDescendant(N->left_);
    }

    Vertex* rightAncestor(Vertex* N) {
        if (N == NULL) { return NULL; }
        else if (N->parent_ != NULL && N->key_ < N->parent_->key_) { return N->parent_; }
        else {
            return rightAncestor(N->parent_);
        }
    }

    Vertex* next(Vertex* N) {
        return (N->right_ == NULL) ? rightAncestor(N) : leftDescendant(N->right_);
    }

    Vertex* find(data_t k, Vertex* R) {
        if (R == NULL) { return NULL; }

        if (R->key_ == k) {
            return R;
        } else if (R->key_ > k) {
            return (R->left_ == NULL) ? R : find(k, R->left_);
        } else {
            return (R->right_ == NULL) ? R : find(k, R->right_);
        }
    }

    void insert(data_t k, char l) {

        Vertex* P = find(k, mRoot);
        if (P->key_ > k) {
            P->left_ = new Vertex(l, P, k);
            P->update();
        } else if (P->key_ < k){
            P->right_ = new Vertex(l, P, k);
            P->update();
        }
    }

    void cutLeft(SplayTree &L, SplayTree &R) {
        R.setRoot(mRoot->right_);
        mRoot->right_ = NULL;
        R.getRoot()->parent_ = NULL;
        L.setRoot(mRoot);
    }

    void cutRight(SplayTree &L, SplayTree &R) {
        L.setRoot(mRoot->left_);
        mRoot->left_ = NULL;
        L.getRoot()->parent_ = NULL;
        R.setRoot(mRoot);
    }

    std::string nodeToString(Vertex* v) {
        std::string s = "";
        if (v->left_) {
            s += nodeToString(v->left_);
        }
        s += v->char_;
        if (v->right_) {
            s+= nodeToString(v->right_);
        }
        return s;
    }

public:

    SplayTree() : mRoot(NULL) {}

    Vertex* getRoot() {
        return mRoot;
    }

    void setRoot(Vertex* R) {
        mRoot = R;
        if (mRoot) { mRoot->parent_ = NULL; }
    }

    void STFind(data_t k) {
        mRoot = find(k,mRoot);
        splay(mRoot);
    }

    void STInsert(data_t k, char l) {

        if (mRoot == NULL) {
            mRoot = new Vertex(l, NULL, k);
            return;
        }
        insert(k, l);
        STFind(k);
    }

    void STDelete(data_t k) {

        if (mRoot == NULL) {
            return;
        }
        if (mRoot->key_ == k && mRoot->left_ == NULL && mRoot->right_ == NULL) {
            mRoot = NULL;
            return;
        }
        STFind(k);

        splay(next(mRoot));
        splay(mRoot);

        if (mRoot->key_ != k) {
            return;
        }
        Vertex* L = mRoot->left_;
        Vertex* R = mRoot->right_;

        if (R == NULL) {
            L->parent_ = NULL;
            mRoot = L;
            return;
        }

        R->left_ = L;
        if (L) { L->parent_ = R; }
        R->parent_ = NULL;
        R->update();
        mRoot = R;
    }

    void STSplit(data_t x, SplayTree &L, SplayTree &R) {
        Vertex* N = find(x, mRoot);
        splay(N);
        if (mRoot->key_ > x) {
            cutLeft(L, R);
        } else if (mRoot->key_< x) {
            cutRight(L, R);
        } else {
            L.setRoot(mRoot);
            R.setRoot(mRoot->right_);
            L.getRoot()->right_ = NULL;
        }
    }

    void STMerge(SplayTree R) {
        Vertex* N = find(INF, mRoot);
        splay(N);
        mRoot->right_ = R.getRoot();
        R.getRoot()->parent_ = mRoot;
    }

    std::string STtoString() {
        return nodeToString(mRoot);
    }

    void print() {
        std::cout << STtoString() << std::endl;
    }
};

class Rope {
private:
    SplayTree mT;
    std::string s;

    void stringToST() {
        mT.setRoot(NULL);
        for (size_t i = 0; i < s.length(); ++i) {
            mT.STInsert(i, s[i]);
        }
    }
public:
    Rope(const std::string &s) : s(s), mT() {
        stringToST();
    }

    void process(data_t i, data_t j, data_t k ) {
        SplayTree sub1, sub2, sub3, sub4;
        stringToST();

        if (i < k) {
            mT.STSplit(i, sub1, sub2);
            sub2.STSplit(j, sub2, sub3);
            sub3.STSplit(k - 1, sub3, sub4);
        } else {
            mT.STSplit(i - 1, sub1, sub3);
            sub3.STSplit(j - 1, sub3, sub4);
            sub1.STSplit(k - 1, sub1, sub2);
        }
        sub2.STMerge(sub4);
        sub1.STMerge(sub3);
        sub1.STMerge(sub2);

        s = sub1.STtoString();

        // Replace this code with a faster implementation
//                std::string t = s.substr(0, i) + s.substr(j + 1);
//                s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
    }

    std::string result() {
        return s;
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    std::string s;
    std::cin >> s;
    Rope rope(s);
    size_t actions;
	std::cin >> actions;
    for (size_t action_index = 0; action_index < actions; ++action_index) {
        data_t i, j, k;
        std::cin >> i >> j >> k;
        rope.process(i, j, k);
    }
	std::cout << rope.result() << std::endl;
}
