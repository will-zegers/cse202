#include <iostream>
#include <vector>
#include <functional>
#include <stdlib.h>
#include <string>

#define DEBUG 0

typedef int64_t data_t;

using std::string;
using std::vector;
using std::cin;

#if DEBUG
    const int SEED = 1237;

    const size_t N_ITER = size_t(1e4);

    const size_t N_MIN = 1;
    const size_t N_MAX = size_t(1e5);
    const size_t P_MAX = size_t(1e8);

    const string ADD  = "add";
    const string DEL  = "del";
    const string FIND = "find";

    const size_t MAX_NAME =  15;
    const string LETTERS = "abcde";

    const time_t T_LIMIT = 3 * 1000;
#endif

const size_t M = size_t(1e4);
const string NOT_FOUND = "not found";

struct Query {
    string type, name;
    data_t number;
};

struct Contact {
    string name;
    data_t number;
};

vector<Query> read_queries() {
    data_t n;
    cin >> n;
    vector<Query> queries(n);
    for (data_t i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector< vector<Contact> >contacts(M, std::vector<Contact>(0));
    for (size_t i = 0; i < queries.size(); ++i) {

        size_t idx = (std::hash<data_t>{}(queries[i].number)) % M;

        if (queries[i].type == "add") {

            vector<Contact> *row = &contacts[idx];
            Contact newContact = {queries[i].name, queries[i].number};

            bool found = false;
            for (vector<Contact>::iterator it = (*row).begin(); it != (*row).end(); ++it) {
                if ((*it).number == newContact.number) {
                    (*it).name = newContact.name;
                    found = true;
                    break;
                }
            }

            if (!found) { (*row).push_back(newContact); }

        } else if (queries[i].type == "del") {

            vector<Contact> *row = &contacts[idx];
            data_t target = queries[i].number;
            for (vector<Contact>::iterator it = (*row).begin(); it != (*row).end(); ++it) {
                if ((*it).number == target) {
                    contacts[idx].erase(it);
                    break;
                }
            }
        } else {

            vector<Contact> *row = &contacts[idx];
            data_t target = queries[i].number;

            bool found = false;
            for (vector<Contact>::iterator it = (*row).begin(); it != (*row).end(); ++it) {
                if ((*it).number == target) {
                    result.push_back((*it).name);
                    found = true;
                }
            }

            if (!found) {
                result.push_back(NOT_FOUND);
            }
        }
    }

    return result;
}

#if DEBUG
vector<Query> generateInput() {

    size_t n = (rand() % (N_MAX + 1 - N_MIN)) + N_MIN;

    vector<Query> queries(n);
    for (size_t i = 0; i < n; ++i) {
        int command = rand() % 3;
        queries[i].number = rand() % P_MAX;

        string qry = "";
        switch(command) {
            case 0: {
                queries[i].type = "add";
                string name = "";
                for (size_t j = 0; j < MAX_NAME; ++j) {
                    name += LETTERS[rand() % LETTERS.size()];
                }
                queries[i].name = name;
                break;
            }
            case 1: {
                queries[i].type = "del";
                break;
            }
            default: {
                queries[i].type = "find";
                break;
            }
        }
        return queries;
    }
}

void testTiming() {

    srand(SEED);
    for (size_t i = 0; i < N_ITER; ++i) {
        vector<Query> q = generateInput();
        time_t start = clock();
        process_queries(q);
        time_t t = clock() - start;
        if (t > T_LIMIT) {
            std::cout << "[-] Time limit exceeded (" << i << ")" << std::endl;
            std::cout << "  Time taken: " << t / 1000 << " s" << std::endl;
            return;
        }
        std::cout << "[+] OK (" << i << ") " << q.size() << " " << t << std::endl;
        std::cout << i << std::endl;
    }
}
#endif

int main() {
#if DEBUG
    testTiming();
#endif
    write_responses(process_queries(read_queries()));
    return 0;
}
