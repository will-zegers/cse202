#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

#define DEBUG 0

typedef int64_t data_t;
typedef int64_t idx_t;

#if DEBUG
const int SEED      = 1234;
const size_t N_ITER = size_t(1e5);
const size_t MIN_MN = size_t(1e0);
const size_t MAX_MN = size_t(1e5);
const int32_t MIN_T = 0;
const int32_t MAX_T = int32_t(1e9);
const time_t MAX_TIME = 1*1000;
#endif

struct Thread {
    int mId;
    data_t mFinishTime;

    Thread(size_t id, data_t finishTime) {
        mId = id;
        mFinishTime = finishTime;
    };

    bool operator <(const Thread& rhs) const {
        if (mFinishTime < rhs.mFinishTime) { return false; }
        if (mFinishTime == rhs.mFinishTime && mId < rhs.mId) { return false; }
        return true;
    }
};

class JobQueue {
private:
    data_t num_workers_;
    vector<data_t> jobs_;

    vector<data_t> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (data_t i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        data_t m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(data_t i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        std::priority_queue<Thread> threads;
        for (size_t i = 0; i < num_workers_; ++i) {
            threads.push(Thread(i,0));
        }
        for (idx_t i = 0; i < jobs_.size(); ++i) {
            Thread t = threads.top();
            threads.pop();
            assigned_workers_[i] = t.mId;
            start_times_[i] = t.mFinishTime;
            t.mFinishTime += jobs_[i];
            threads.push(t);
        }
        return;
    }

#if DEBUG
    void GenerateData() {
        srand(SEED);
        num_workers_ = (data_t)((rand() % (MAX_MN + 1 - MIN_MN)) + MIN_MN);
        size_t m = (rand() % (MAX_MN + 1 - MIN_MN)) + MIN_MN;
        jobs_.resize(m);
        for(data_t i = 0; i < m; ++i) {
            jobs_[i] = (rand() % (MAX_T + 1 - MIN_T)) + MIN_T;
        }
    }

    void naive_AssignJobs() {
        // TODO: replace this code with a faster algorithm.
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        vector<long long> next_free_time(num_workers_, 0);
        for (data_t i = 0; i < jobs_.size(); ++i) {
            data_t duration = jobs_[i];
            data_t next_worker = 0;
            for (data_t j = 0; j < num_workers_; ++j) {
                if (next_free_time[j] < next_free_time[next_worker])
                    next_worker = j;
            }
            assigned_workers_[i] = next_worker;
            start_times_[i] = next_free_time[next_worker];
            next_free_time[next_worker] += duration;
        }
    }
#endif

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }

#if DEBUG
    bool TestTiming() {
        GenerateData();

        time_t start = clock();
        AssignJobs();
        time_t t = clock() - start;

        if (t > MAX_TIME) {
            for (size_t j = 0; j < jobs_.size(); ++j) {
                std::cout << jobs_[j] << " ";
            }
            for (size_t j = 0; j < jobs_.size(); ++j) {
                std::cout << assigned_workers_[j] << " " << start_times_[j];
                std::cout << std::endl;
            }
            return false;

        }
        return true;
    }

    bool TestSolution() {
        GenerateData();
//        ReadData();

        AssignJobs();
        vector<data_t> fast_assigned = assigned_workers_;
        vector<long long> fast_starts = start_times_;
        naive_AssignJobs();
        vector<data_t> naive_assigned = assigned_workers_;
        vector<long long> naive_starts = start_times_;


        for (size_t i = 0; i < jobs_.size(); ++i) {
            if (fast_assigned[i] != naive_assigned[i] || fast_starts[i] != naive_starts[i]) {
                for (size_t j = 0; j < jobs_.size(); ++j) {
                    std::cout << jobs_[j] << " ";
                }
                for (size_t j = 0; j < jobs_.size(); ++j) {
                    std::cout << fast_assigned[j] << " " << fast_starts[j] << " | ";
                    std::cout << naive_assigned[j] << " " << naive_starts[j];
                    std::cout << std::endl;
                }
                return false;
            }
        }
        return true;
    }
#endif
};

void print_queue(std::priority_queue<Thread> q) {
    while(!q.empty()) {
        std::cout << q.top().mId << " | " << q.top().mFinishTime;
        std::cout << std::endl;
        q.pop();
    }
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;

#if DEBUG
    for (size_t i = 0; i < N_ITER && job_queue.TestTiming(); ++i) {
        std::cout << "[+] OK (" << i << ")" << std::endl;
    }
#else
    job_queue.Solve();
#endif
    return 0;
}
