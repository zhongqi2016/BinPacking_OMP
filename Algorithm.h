
#ifndef BINPACKING_BNB_ALGORITHM_H
#define BINPACKING_BNB_ALGORITHM_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <stack>
#include <omp.h>
#include "Bound.h"

class BinPacking {
public:
    BinPacking(int _c, std::vector<int> _weight) : c(_c), weightOfItems(_weight),
                                                                     num_threads(0), UB(0),
                                                                     solution(std::vector<int>(_weight.size(), 0)),foundRes(false) {}

    int BNB();

    std::vector<int> &getSolution() { return solution; }

    void printSolution();

    void setNumThreads(int numThreads){num_threads=numThreads;}

private:
    void dfs(std::stack<Bound> s);

    void organize();

    const int c;//capacity of bin
    int UB;
    int LB;
    int num_threads;
    bool foundRes;
    std::vector<int> weightOfItems;
    std::vector<int> solution;
};


#endif //BINPACKING_BNB_ALGORITHM_H

