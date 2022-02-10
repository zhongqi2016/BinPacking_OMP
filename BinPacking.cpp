
#include "BinPacking.h"

int BinPacking::BNB() {
    std::vector<Item> items = refactor(weightOfItems);
    sort(items.rbegin(), items.rend());
    Branch *branch = new Branch(c, items);

    branch->reduction();
    solution = branch->getDistribution();
    LB = branch->lowerBound2();
    _UB.store(branch->upperBound(solution));

    if (_UB == LB) {
        organize();
        return _UB;
    }
    LB = branch->lowerBound3();
    if (_UB == LB) {
        organize();
        return _UB;
    }
#pragma omp parallel shared(branch) default(none)
    {
#pragma omp single
        {
            bfs(branch);
        }
    }
    organize();
    return _UB;
}

void BinPacking::bfs(Branch *branch) {
    ++countBranches;
    int z = branch->getIndexOfItem();
    std::vector<Item> &items = branch->getItems();
    if (z == items.size() || items[z].weight == 0) return;

    //to all feasible initialized bins
    int j;
    z = branch->getIndexOfItem();
    for (j = z - 1; j >= 0 && !foundRes; --j) {
        if (items[j].weight + items[z].weight <= c) {
//                int z1 = z;
            Branch *newBranch = new Branch(*branch);
            newBranch->mergeTwoItems(j, z);
            newBranch->reduction();
            std::vector<int> curSolution(newBranch->getDistribution());
            int LB_current = newBranch->lowerBound2();
            int UB_current = newBranch->upperBound(curSolution);

            if (UB_current == LB) {
                solution = std::move(curSolution);
                _UB.store(UB_current);
                foundRes.store(true);
                delete newBranch;
                delete branch;
                return;
            }

            int UB = _UB.load();
            while (UB > UB_current) {
                solution = std::move(curSolution);
                if (_UB.compare_exchange_weak(UB, UB_current)) {
                    UB = _UB.load();
                    break;
                }
            }

            if (UB_current > LB_current && LB_current < UB) {
                if (newBranch->getIndexOfItem() + newBranch->getReduced() < UB) {
                    if (newBranch->lowerBound3() < UB) {
#pragma omp task shared(newBranch) default(none)
                        bfs(newBranch);
                    }
                }
            }

        }
    }

    //create a new bin
    if (z + branch->getReduced() < _UB) {
        Branch *newBranch = new Branch(*branch);
//        newBranch->addCurrentItem();
        newBranch->incrementIndex();
        newBranch->reduction();

        std::vector<int> curSolution(newBranch->getDistribution());
        int LB_current = newBranch->lowerBound2();
        int UB_current = newBranch->upperBound(curSolution);

        if (UB_current == LB) {
            solution = std::move(curSolution);
            _UB.store(UB_current);
            foundRes.store(true);
            delete newBranch;
            delete branch;
            return;
        }
        int UB = _UB.load();
        while (UB > UB_current) {
            solution = std::move(curSolution);
            if (_UB.compare_exchange_weak(UB, UB_current)) {
                UB = _UB.load();
                break;
            }
        }


        if (UB_current > LB_current && LB_current < UB) {

            if (newBranch->getIndexOfItem() + newBranch->getReduced() < UB) {
                if (newBranch->lowerBound3() < UB) {
#pragma omp task shared(newBranch) default(none)
                    bfs(newBranch);
                }
            }

        }

    }
    delete branch;
}

void BinPacking::organize() {
    int min = *std::min_element(solution.begin(), solution.end());
    if (min < 0) min = -min;
    else return;
    for (int &elem: solution) {
        if (elem < 0)elem += min + 1;
        else if (elem > 0) elem += min;
    }
}

void BinPacking::printSolution1() {
    for (auto index: solution) {
        printf("%d ", index);
    }
    printf("\n");
}

void BinPacking::printSolution2() {
    std::vector<std::vector<int>> res(_UB.load());
    for (int i = 0; i < solution.size(); ++i) {
        res[solution[i] - 1].push_back(i);
    }
    for (auto &bin: res) {
        printf("{");
        for (int item: bin) {
            printf("%d,", item);
        }
        printf("},");
    }
    printf("\n");
}