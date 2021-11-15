
#ifndef BINPACKING_BNB_ALGORITHM_H
#define BINPACKING_BNB_ALGORITHM_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <stack>
#include <omp.h>
#include <atomic>
#include "Branch.h"

class BinPacking {
public:
    BinPacking(int _c, std::vector<int> _weight) : c(_c), weightOfItems(_weight),
                                                   _UB(0),
                                                   solution(std::vector<int>(_weight.size(), 0)), foundRes(false) {}

    int BNB();

    std::vector<int> &getSolution() { return solution; }

    void printSolution();


private:
    void dfs(Branch *branch);

    void organize();

    const int c;//capacity of bin
    std::atomic<int> _UB;
    int LB;
    std::atomic<bool> foundRes;
    std::vector<int> weightOfItems;
    std::vector<int> solution;//Current optimal solution
};


#endif //BINPACKING_BNB_ALGORITHM_H

