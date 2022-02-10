
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
                                                   _UB(0),countBranches(0),
                                                   solution(std::vector<int>(_weight.size(), 0)), foundRes(false) {}

    int BNB();

    std::vector<int> &getSolution() { return solution; }

    //solution: 1,1,2,2,3,3,
    //the number is serial of bin where each item is located
    void printSolution1();

    //solution: {1,2,},{3,4,},{5,6,}
    //the number above is the number of each item. Items in a bracket will be placed in the same box.
    void printSolution2();

    int getCountBranches(){
        return countBranches;
    }

private:
    void bfs(Branch *branch);

    void organize();

    const int c;//capacity of bin
    std::atomic<int> _UB;
    std::atomic<int> countBranches;
    int LB;
    std::atomic<bool> foundRes;
    std::vector<int> weightOfItems;
    std::vector<int> solution;//Current optimal solution
};


#endif //BINPACKING_BNB_ALGORITHM_H

