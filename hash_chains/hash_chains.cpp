#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

#define DEBUG 0

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
private:
    size_t bucket_count;
    // store all strings in one vector
//    vector<string> elems;
    vector< vector<string> > elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int64_t i = static_cast<int64_t> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(size_t bucket_count): bucket_count(bucket_count) {
        elems = vector< vector<string> >(bucket_count, vector<string>(0));
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {

        if (query.type == "check") {
            vector<string> row = elems[query.ind];
            // use reverse order, because we append strings to the end
            for (vector<string>::reverse_iterator it = row.rbegin(); it != row.rend(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        } else {
            size_t idx = hash_func(query.s);
            vector<string>::iterator it = std::find(elems[idx].begin(), elems[idx].end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems[idx].end());
            else if (query.type == "add") {
                if (it == elems[idx].end())
                    elems[idx].push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems[idx].end())
                    elems[idx].erase(it);
            }
        }
    }

    void processQueries() {
        size_t n;
        cin >> n;
        for (size_t i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

#if DEBUG

const size_t N_ITER = size_t(1e0);

const size_t MIN_N  = size_t(1e1);
const size_t MAX_N  = size_t(1e5);

const size_t MAX_S  = 15;

class Tester {
private:

    QueryProcessor proc;

    void generateInput() {
        size_t n = (rand() % (MAX_N + 1 - MIN_N)) + MIN_N;

        const size_t MIN_M  = n/5;
        const size_t MAX_M  = n;
        size_t n = (rand() % (MAX_M + 1 - MIN_M)) + MIN_M;
        proc.setBucketCount(m);

        for (size_t i = 0; i < n; ++i) {
            Query query;
            query.type = generateCommand();
            if (query.type != "check")
                query.s = generateString();
            else
                query.ind = (rand() % m);
            return query;
        }
    }

    string generateString() {
        const string LETTERS = "abcdefghijklmnopqrstuvwxyz";
        size_t n = rand() % MAX_S;

        string str = "";
        for (size_t i = 0; i < n; ++i) {
            str += LETTERS[rand() % LETTERS.size()];
        }
        return str;
    }

    string generateCommand() {
        int32_t r = rand() % 4;
        switch(r) {
            case 0: return "add";
            case 1: return "del";
            case 2: return "find";
            case 3: return "check";
        }
    }

public:
    Tester(size_t iterations) {
        proc = new QueryProcessor(0);
    }

};
#endif

int main() {
    std::ios_base::sync_with_stdio(false);
    size_t bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
