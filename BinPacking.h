
#ifndef BINPACKING_BNB_ALGORITHM_H
#define BINPACKING_BNB_ALGORITHM_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <stack>
#include <omp.h>
#include <mpi.h>
#include <atomic>
#include <cstring>

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "Branch.h"

#define id_root 0

class BinPacking {
public:
    BinPacking(int _c, std::vector<int> _weight, int _numThreads) : c(_c), weightOfItems(_weight),
                                                                    _UB(0), countBranches(0), numThreads(_numThreads),
                                                                    solution(std::vector<int>(_weight.size(), 0)),
                                                                    foundRes(false), busy(0), isClosed(false) {
        MPI_Comm_rank(MPI_COMM_WORLD, &id_MPI);
    }


    Branch init();

    void BNB(Branch branch);

    void bfs(Branch branch);

    static BinPacking dataDeserialize(int *inputData, int numThreads);

    std::vector<int> getSerializeInputData();

    std::vector<int> branchSerialization(Branch &branch) const;

    Branch branchDeserialize(int *inputMessage);

    void sendRequestToMaster();

    std::vector<int> &getSolution() { return solution; }

    //solution: 1,1,2,2,3,3,
    //the number is serial of bin where each item is located
    void printSolution1();

    //solution: {1,2,},{3,4,},{5,6,}
    //the number above is the number of each item. Items in a bracket will be placed in the same box.
    void printSolution2();

    int getCountBranches() {
        return countBranches;
    }

    bool resFound() { return foundRes.load(); }

private:
    //----ThreadPool---
    void initThreadPool() {
        for (int i = 0; i < numThreads; ++i) {
            std::thread(&BinPacking::worker, this).detach();
        }
    }

    void worker() {
        std::unique_lock<std::mutex> locker(mtx);
        while (true) {
            if (!workQueue.empty()) {
                ++busy;
                Branch task = std::move(workQueue.top());
                workQueue.pop();
                locker.unlock();
                bfs(std::move(task));
                locker.lock();
                --busy;
                finished.notify_one();
            } else if (isClosed) break;
            else {
                cond.wait(locker);
            }
        }
    }

    void append(Branch &&task) {
        std::lock_guard<std::mutex> locker(mtx);
        workQueue.emplace(std::forward<Branch>(task));

        cond.notify_one();
    }

    void waitForFinished() {
        std::unique_lock<std::mutex> lock(mtx);
        finished.wait(lock, [this]() { return workQueue.empty() && (busy == 0); });
    }

    void clearQueue() {
        std::lock_guard<std::mutex> locker(mtx);
        std::stack<Branch> empty;
        swap(empty, workQueue);
    }

    void endThreadPool() {
        isClosed = true;

        cond.notify_all();

    }

private:

    void organize();

    int id_MPI;
    //pool
    std::mutex mtx;
    std::atomic<bool> isClosed;
    std::stack<Branch> workQueue;
    std::condition_variable cond;
    std::condition_variable finished;
    unsigned int busy;

    //
    int numThreads;

    int c;//capacity of bin
    std::atomic<int> _UB;
    std::atomic<int> countBranches;
    std::atomic<int> numberOfTasks;
    int LB{};
    std::atomic<bool> foundRes;
    std::vector<int> weightOfItems;
    std::vector<int> solution;//Current optimal solution
};


#endif //BINPACKING_BNB_ALGORITHM_H

