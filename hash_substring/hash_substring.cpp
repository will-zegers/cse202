#include <iostream>
#include <string>
#include <vector>

const uint64_t PRIME = (2<<31)-1;

struct Data {
    std::string pattern, text;
};

uint64_t polyHash(std::string S, uint64_t p, uint64_t x) {

    uint64_t h = 0;
    uint64_t x_poly = 1;
    for (size_t i = 0; i < S.length(); ++i) {
        h += (static_cast<uint64_t>(S[i]) * x_poly) % p;

        x_poly = (x * x_poly) % p;
    }

    return h;
//    return ((h % p) + p) % p;
}

void precomputeHashes(std::string T, std::string P, uint64_t p, uint64_t x, std::vector<uint64_t> &H) {

    std::string S;
    for (size_t c = T.size() - P.size(); c < T.size(); ++c) {
        S += T[c];
    }

    H[T.size() - P.size()] = polyHash(S, p, x);
    uint64_t y = 1;
    for (size_t i = 0; i < P.size(); ++i) {
        y = (y * x) % p;
    }

    for (int32_t i = T.size() - P.size() - 1; i >=0; --i) {
        H[i] = (x*H[i+1] + T[i] - y * T[i+P.size()]) % p;
    }
}

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<size_t>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<size_t> get_occurrences(const Data& input) {

    const uint64_t X = random() % PRIME;

    const std::string& p = input.pattern;
    const std::string& t = input.text;

    std::vector<size_t> ans;
    std::vector<uint64_t> H(t.size() - p.size() + 1);

    uint64_t h = polyHash(p, PRIME, X);
    precomputeHashes(t, p, PRIME, X, H);
    for (size_t i = 0; i < H.size(); ++i) {
        if (H[i] == h) { ans.push_back(i); }
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::vector<uint64_t> H;

//    precomputeHashes("abacaba", "aba", PRIME, X, H);
//    for (size_t i = 0; i < H.size(); ++i) {
//        std::cout << H[i] << std::endl;
//    }
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
