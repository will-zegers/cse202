#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
    int32_t start;
    int32_t end;
    bool operator <(const Segment& rhs) const { return start < rhs.start; }
};

vector<int32_t> optimal_points(vector<Segment> &segments) {
    vector<int32_t> points;

    uint8_t n;
    int32_t start, end;

    std::sort(segments.begin(), segments.end());

    n = segments.size();
    for (size_t i = 0; i < n;) {
        start = segments[i].start;
        end = segments[i].end;
        while(segments[++i].start <= end && i < n) {
            start = std::max(segments[i].start, start);
            end = std::min(segments[i].end, end);
        }
        points.push_back(rand() % (end - start + 1) + start);
    }
    return points;
}

int main() {
    uint16_t n;
    srand(1234);

    std::cin >> n;

    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }

    vector<int32_t> points = optimal_points(segments);

    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
