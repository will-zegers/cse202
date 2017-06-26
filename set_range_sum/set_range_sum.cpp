#include <cstdio>
#include <iostream>

#define DEBUG 0

typedef long long int data_t;

// Splay tree implementation

//// Vertex of a splay tree
//struct Vertex {
//  data_t key;
//  // Sum of all the keys in the subtree - remember to update
//  // it after each operation that changes the tree.
//  long long STSum;
//  Vertex* left;
//  Vertex* right;
//  Vertex* parent;
//
//  Vertex(data_t key, long long STSum, Vertex* left, Vertex* right, Vertex* parent)
//  : key(key), sum(STSum), left(left), right(right), parent(parent) {}
//};
//
//void update(Vertex* v) {
//  if (v == NULL) return;
//  v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->STSum : 0ll);
//  if (v->left != NULL) {
//    v->left->parent = v;
//  }
//  if (v->right != NULL) {
//    v->right->parent = v;
//  }
//}
//
//void small_rotation(Vertex* v) {
//  Vertex* parent = v->parent;
//  if (parent == NULL) {
//    return;
//  }
//  Vertex* grandparent = v->parent->parent;
//  if (parent->left == v) {
//    Vertex* m = v->right;
//    v->right = parent;
//    parent->left = m;
//  } else {
//    Vertex* m = v->left;
//    v->left = parent;
//    parent->right = m;
//  }
//  update(parent);
//  update(v);
//  v->parent = grandparent;
//  if (grandparent != NULL) {
//    if (grandparent->left == parent) {
//      grandparent->left = v;
//    } else {
//      grandparent->right = v;
//    }
//  }
//}
//
//void big_rotation(Vertex* v) {
//  if (v->parent->left == v && v->parent->parent->left == v->parent) {
//    // Zig-zig
//    small_rotation(v->parent);
//    small_rotation(v);
//  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
//    // Zig-zig
//    small_rotation(v->parent);
//    small_rotation(v);
//  } else {
//    // Zig-zag
//    small_rotation(v);
//    small_rotation(v);
//  }
//}
//
//// Makes splay of the given vertex and makes
//// it the new root.
//void splay(Vertex*& root, Vertex* v) {
//  if (v == NULL) return;
//  while (v->parent != NULL) {
//    if (v->parent->parent == NULL) {
//      small_rotation(v);
//      break;
//    }
//    big_rotation(v);
//  }
//  root = v;
//}
//
//// Searches for the given key in the tree with the given root
//// and calls splay for the deepest visited node after that.
//// If found, returns a podata_ter to the node with the given key.
//// Otherwise, returns a podata_ter to the node with the smallest
//// bigger key (next value in the order).
//// If the key is bigger than all keys in the tree,
//// returns NULL.
//Vertex* find(Vertex*& root, data_t key) {
//  Vertex* v = root;
//  Vertex* last = root;
//  Vertex* next = NULL;
//  while (v != NULL) {
//    if (v->key >= key && (next == NULL || v->key < next->key)) {
//      next = v;
//    }
//    last = v;
//    if (v->key == key) {
//      break;
//    }
//    if (v->key < key) {
//      v = v->right;
//    } else {
//      v = v->left;
//    }
//  }
//  splay(root, last);
//  return next;
//}
//
//void split(Vertex* root, data_t key, Vertex*& left, Vertex*& right) {
//  right = find(root, key);
//  splay(root, right);
//  if (right == NULL) {
//    left = root;
//    return;
//  }
//  left = right->left;
//  right->left = NULL;
//  if (left != NULL) {
//    left->parent = NULL;
//  }
//  update(left);
//  update(right);
//}
//
//Vertex* merge(Vertex* left, Vertex* right) {
//  if (left == NULL) return right;
//  if (right == NULL) return left;
//  Vertex* min_right = right;
//  while (min_right->left != NULL) {
//    min_right = min_right->left;
//  }
//  splay(right, min_right);
//  right->left = left;
//  update(right);
//  return right;
//}
//
//// Code that uses splay tree to solve the problem
//
//Vertex* root = NULL;
//
//void insert(data_t x) {
//  Vertex* left = NULL;
//  Vertex* right = NULL;
//  Vertex* new_vertex = NULL;
//  split(root, x, left, right);
//  if (right == NULL || right->key != x) {
//    new_vertex = new Vertex(x, x, NULL, NULL, NULL);
//  }
//  root = merge(merge(left, new_vertex), right);
//}
//
//void erase(data_t x) {
//  // Implement erase yourself
//
//}
//
//bool find(data_t x) {
//  // Implement find yourself
//
//  return false;
//}
//
//long long STSum(data_t from, data_t to) {
//  Vertex* left = NULL;
//  Vertex* middle = NULL;
//  Vertex* right = NULL;
//  split(root, from, left, middle);
//  split(middle, to + 1, middle, right);
//  long long ans = 0;
//  // Complete the implementation of STSum
//
//  return ans;
//}

struct Vertex {
    data_t key_;
    data_t sum_;
    data_t size_;
    Vertex* parent_;
    Vertex* left_;
    Vertex* right_;

    Vertex(Vertex* P = NULL, data_t k = 0) :
            key_(k),
            sum_(k),
            size_(1),
            parent_(P),
            left_(NULL),
            right_(NULL) {}

    void update() {
        size_ = 1;
        sum_ = key_;
        if (left_ != NULL) {
            size_ += left_->size_;
            sum_ += left_->sum_;
        }
        if (right_ != NULL) {
            size_ += right_->size_;
            sum_ += right_->sum_;
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

    void insert(data_t k) {

        Vertex* P = find(k, mRoot);
        if (P->key_ > k) {
            P->left_ = new Vertex(P, k);
            P->update();
        } else if (P->key_ < k){
            P->right_ = new Vertex(P, k);
            P->update();
        }
    }


public:

    SplayTree(Vertex* root) : mRoot(root) {}

    Vertex* root() {
        return mRoot;
    }

    void STFind(data_t k) {
        mRoot = find(k,mRoot);
        splay(mRoot);
    }

    void STInsert(data_t k) {

        if (mRoot == NULL) {
            mRoot = new Vertex(NULL, k);
            return;
        }
        insert(k);
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

    long long STSum(data_t l, data_t r) {

        if (mRoot == NULL) { return 0; }
        STFind(l);

        long long x = 0;
        if (mRoot->key_ >= l) {
            x += mRoot->sum_;
            if (mRoot->left_) { x -= mRoot->left_->sum_; }
        } else if (mRoot->right_) { x+= mRoot->right_->sum_;}

        STFind(r);
        if (mRoot->right_) { x -= mRoot->right_->sum_; };
        if (mRoot->key_ > r) { x -= mRoot->key_; }

        return x;
    }
};

const data_t MODULO = 1000000001;

#if DEBUG
int main() {

    srand(SEED);

    for (size_t i = 0; i < N_ITER; ++i) {
        Vertex* T = NULL;
        vector<data_t> V;

        data_t x = 0;
        vector<string> history;

        size_t n = (rand() % (MAX_N + 1 - MIN_N)) + MIN_N;
        time_t start = clock();
        for (size_t j = 0; j < n; ++j) {

            string cmd, stFind, nvFind;
            data_t k, l, r;
            data_t nvSum, stSum;
            int op = rand() % 4;
            switch (op) {
                case 0:
                    k = (random() % (MAX_I + 1 - MIN_I)) + MIN_I;
//                    cmd = "+ " + patch::to_string(k);
//                    std::cout << cmd << std::endl;
//                    history.push_back(cmd);
                    T = STInsert((x + k) % MODULO, T);
//                    naiveInsert((x + k) % MODULO, V);
                    break;
                case 1:
                    k = (random() % (MAX_I + 1 - MIN_I)) + MIN_I;
//                    cmd = "- " + patch::to_string(k);
//                    std::cout << cmd << std::endl;
//                    history.push_back("cmd");
                    T = STDelete((x + k) % MODULO, T);
//                    naiveDelete((x + k) % MODULO, V);
                    break;
                case 2:
                    k = (random() % (MAX_I + 1 - MIN_I)) + MIN_I;
//                    cmd = "? " + patch::to_string(k);
//                    std::cout << cmd << std::endl;
//                    history.push_back(cmd);
                    T = STFind((x + k) % MODULO, T);
                    stFind = (T != NULL  && T->key_ == (x + k) % MODULO) ? "Found" : "Not found";
//                    std::cout << stFind << std::endl;
//                    nvFind = (naiveFind((x + k) % MODULO, V)) ? "Found" : "Not found";
//                    std::cout << "Naive: " << nvFind << std::endl;
//                    if (stFind.compare(nvFind) != 0) {
//                        std::cout << "[-] Mismatch! (" << j << ")" << std::endl;
//                        return -1;
//                    }
                    break;
                default:
                    l = (random() % (MAX_I + 1 - MIN_I)) + MIN_I;
                    r = (random() % (MAX_I + 1 - l)) + l;
//                    cmd = "s " + patch::to_string(l) + " " + patch::to_string(r);
//                    std::cout << cmd << std::endl;
//                    history.push_back(cmd);
                    stSum = STSum((l + x) % MODULO, (r + x) % MODULO, T);
//                    std::cout << stSum << std::endl;
//                    nvSum = naiveSum((l + x) % MODULO, (r + x) % MODULO, V);
//                    std::cout << "Naive: " << nvSum << std::endl;
//                    if (stSum != nvSum) {
//                        std::cout << "[-] Mismatch! (" << j << ")" << std::endl;
//                        return -1;
//                    }
                    x = stSum;
                    break;
            }
//            std::cout << "<-- ";
//            if (T != NULL) { printTreeKeys(T); }
//            std::cout << "-->" << std::endl;
//            printVectorKeys(V);
        }
        time_t dur = clock() - start;
        std::cout << (float)dur/CLOCKS_PER_SEC << std::endl;
    }
}
#else
int main(){
    int n;
//    Vertex* T = NULL;
    SplayTree T(NULL);
    scanf("%d", &n);
    data_t last_sum_result = 0;
    for (data_t i = 0; i < n; i++) {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type) {
            case '+' : {
                data_t x;
                scanf("%lld", &x);
                data_t k = (x + last_sum_result) % MODULO;
                T.STInsert(k);
            } break;
            case '-' : {
                data_t x;
                scanf("%lld", &x);
                data_t k = (x + last_sum_result) % MODULO;
                T.STDelete(k);
            } break;
            case '?' : {
                data_t x;
                scanf("%lld", &x);
                data_t k = (x + last_sum_result) % MODULO;
                T.STFind(k);
                printf((T.root() != NULL && T.root()->key_ == k) ? "Found\n" : "Not found\n");
            } break;
            case 's' : {
                data_t l, r;
                scanf("%lld %lld", &l, &r);
                long long res = T.STSum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
                printf("%lld\n", res);
                last_sum_result = res % MODULO;
            }
            default: break;
        }
    }
    return 0;
}
#endif
