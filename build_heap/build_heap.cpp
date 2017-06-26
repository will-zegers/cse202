#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

typedef int32_t data_t;

class HeapBuilder {
private:
    vector<data_t> data_;
    vector< pair<data_t, data_t> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void GenerateSwaps() {
        data_t n = (data_t)data_.size();

        for (data_t i = (n>>1); i >= 0; --i) {
            data_t max_idx = i;
            for(;;) {
                data_t t_idx = max_idx;
                data_t l_idx = (max_idx<<1)+1;
                data_t r_idx = l_idx+1;
                if (l_idx < n && data_[max_idx] > data_[l_idx]) {
                    max_idx = l_idx;
                }
                if (r_idx < n && data_[max_idx] > data_[r_idx]) {
                    max_idx = r_idx;
                }
                if (max_idx != t_idx) {
                    swap(data_[t_idx], data_[max_idx]);
                    swaps_.push_back(make_pair(t_idx, max_idx));
                } else { break; }
            }
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
