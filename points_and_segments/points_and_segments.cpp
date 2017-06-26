#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

const size_t SP_MIN  = 1;
const size_t SP_MAX  = size_t(5e4);
const int_fast32_t ABX_MIN  = int_fast32_t(-1e8);
const int_fast32_t ABX_MAX  = int_fast32_t(1e8);
const time_t T_MAX  = 3 * CLOCKS_PER_SEC;
const size_t N_ITER = size_t(1e3);

enum point_type {
    point,
    left,
    right
};

struct Segment {
    int_fast32_t a;
    int_fast32_t b;
    bool operator <(const Segment& rhs) const {
      if (a < rhs.a) { return true; }
      if (a == rhs.a && b < rhs.b) { return true; }
      return false;
    }
};

struct Pair {
    int_fast32_t idx;
    int_fast32_t value;
    point_type t;
    bool operator <(const Pair& rhs) const {
      if (value < rhs.value) { return true; }
      if (value == rhs.value) {
        if (t == left && rhs.t == point) { return true;}
        if (t == point && rhs.t == right) { return true; }
        if (t == left && rhs.t == right) { return true;}
      }
      return false;
    }
};

vector<int_fast32_t> fast_count_segments(vector<Segment> segments, vector<int_fast32_t> points) {

  size_t i, j;
  vector<Pair> pairs(points.size() + 2*segments.size());
  vector<int_fast32_t> count(points.size(), 0);

  for (i = 0; i < points.size(); ++i) {
    pairs[i].value = points[i];
    pairs[i].t = point;
    pairs[i].idx = i;
  }
  for (i = points.size(), j = 0; i < pairs.size(); i += 2, ++j) {
    pairs[i].value = segments[j].a;
    pairs[i].t = left;
    pairs[i].idx = -1;
    pairs[i+1].value = segments[j].b;
    pairs[i+1].t = right;
    pairs[i+1].idx = -1;
  }

  std::sort(pairs.begin(), pairs.end());

  int_fast32_t cnt = 0;
  for (i = 0; i < pairs.size(); ++i) {
    if (pairs[i].t == left) { ++cnt; }
    if (pairs[i].t == right) { --cnt; }
    if (pairs[i].t == point) {
      count[pairs[i].idx] = cnt;
    }
  }

  return count;
}

vector<int_fast32_t> naive_count_segments(vector<Segment> segments, vector<int_fast32_t> points) {
  vector<int_fast32_t> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < segments.size(); j++) {
      cnt[i] += segments[j].a <= points[i] && points[i] <= segments[j].b;
    }
  }
  return cnt;
}

void test_solution() {
  srand(12340);

  size_t i, j, k, s, p;
  vector<int_fast32_t> naive, fast;

  for (i = 0; i < N_ITER; ++i) {
    s = (rand() % (SP_MAX + 1 - SP_MIN)) + SP_MIN;
    p = (rand() % (SP_MAX + 1 - SP_MIN)) + SP_MIN;

    vector<Segment> segments (s);
    for (j =0; j < s; ++j) {
      segments[j].a = (rand() % (ABX_MAX + 1 - ABX_MIN)) + ABX_MIN;
      // a = (rand() % 100) + 1
      segments[j].b = (rand() % (ABX_MAX + 1 - segments[j].a)) + segments[j].a;
      // b = (rand() % (100 - a
    }

    vector<int_fast32_t> points(p);
    for (j = 0; j < points.size(); ++j) {
      points[j] = (rand() % (ABX_MAX + 1 - ABX_MIN)) + ABX_MIN;
    }

    naive = naive_count_segments(segments, points);
    fast = fast_count_segments(segments, points);

    for (j = 0; j < points.size(); ++j) {
      if (naive[j] != fast[j]) {
        std::cout << "[-] Mismatch (" << i << ")" << std::endl;
        std::cout << "  Segments: " << std::endl;
        std::sort(segments.begin(), segments.end());
        for (k = 0; k < segments.size(); ++k){
          std::cout << "    " << segments[k].a << " " << segments[k].b << std::endl;
        }

        std::cout << "  Problem point: " << points[j] << std::endl;

        std::cout << "  Points: " << std::endl;
        for (k = 0; k < points.size(); ++k){
          std::cout << points[k] << " ";
        }
        std::cout << std::endl;

        std::cout << "  Naive: ";
        for (k = 0; k < naive.size(); ++k){
          std::cout << naive[k] << " ";
        }
        std::cout << std::endl;
        std::cout << "  Fast: ";
        for (k = 0; k < fast.size(); ++k){
          std::cout << fast[k] << " ";
        }
        std::cout << std::endl;
        return;
      }
    }
    std::cout << "[OK] (" << i << ")" << std::endl;
  }
}

void test_timing() {
  srand(1234);

  size_t i, j, k, s, p;
  clock_t t;

  for (i = 0; i < N_ITER; ++i) {
    s = (rand() % (SP_MAX + 1 - SP_MIN)) + SP_MIN;
    p = (rand() % (SP_MAX + 1 - SP_MIN)) + SP_MIN;

    vector<Segment> segments (s);
    for (j =0; j < s; ++j) {
      segments[j].a = (rand() % (ABX_MAX + 1 - ABX_MIN)) + ABX_MIN;
      // a = (rand() % 100) + 1
      segments[j].b = (rand() % (ABX_MAX + 1 - segments[j].a)) + segments[j].a;
      // b = (rand() % (100 - a
    }

    vector<int_fast32_t> points(p);
    for (j = 0; j < points.size(); ++j) {
      points[j] = (rand() % (ABX_MAX + 1 - ABX_MIN)) + ABX_MIN;
    }

    t = clock();
    fast_count_segments(segments, points);
    t = clock() - t;
    if (t > T_MAX) {
      std::cout << "[-] Time exceeded (" << i << ")" << std::endl;
      std::cout << "    Time elapsed: " << (double)t/1000 << " s" << std::endl;
      break;
    }

    std::cout << "[+] OK (" << i << ") t=" << (double)t/1000 << " s" << std::endl;
  }
}

int main() {
//  test_solution();
//  test_timing();
  int n, m;
  std::cin >> n >> m;

  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].a >> segments[i].b;
  }

  vector<int_fast32_t> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int_fast32_t> cnt = fast_count_segments(segments, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
