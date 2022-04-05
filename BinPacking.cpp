
#include "BinPacking.h"

BinPacking BinPacking::dataDeserialize(int *inputData, int numThreads) {
    int itemsSize = inputData[0];
    int c = inputData[1];
    std::vector<int> items(itemsSize);
    std::memcpy(items.data(), &inputData[2], itemsSize);
    return {c, items, numThreads};
}

std::vector<int> BinPacking::getSerializeInputData() {
    std::size_t itemsSize = weightOfItems.size();
    std::vector<int> list(itemsSize + 2);
    list[0] = itemsSize;
    list[1] = c;
    std::memcpy(&list[2], weightOfItems.data(), itemsSize);
    return list;
}

inline std::vector<int> BinPacking::branchSerialization(Branch &branch) const {
    std::vector<int> data = std::move(branch.serialization());
    data[0] = _UB.load();
    data[1] = LB;
    return data;
}

Branch BinPacking::branchDeserialize(int *inputMessage) {
    if (inputMessage[0] < _UB) _UB = inputMessage[0];
    int c = inputMessage[2];
    int reduced = inputMessage[3];
    int indexOfItem = inputMessage[4];
    std::vector<Item> items;
    items.reserve(inputMessage[5]);
    int index = 6;
    int end = inputMessage[5] * 2 + index;
    for (; index < end; index += 2) {
        Item item{inputMessage[index], inputMessage[index + 1]};
        items.emplace_back(std::move(item));
    }
    std::vector<int> distribution;
    distribution.reserve(inputMessage[index]);
    end = inputMessage[index] + index + 1;
    ++index;
    for (; index < end; ++index) {
        distribution.emplace_back(inputMessage[index]);
    }
    return Branch{c, reduced, indexOfItem, items, distribution};
}

inline void BinPacking::sendRequestToMaster() {
    int command[2] = {3, 0};
    MPI_Send(command, 2, MPI_INT, id_root, 0, MPI_COMM_WORLD);
}




Branch BinPacking::init() {
    std::vector<Item> items = refactor(weightOfItems);
    sort(items.rbegin(), items.rend());
    Branch branch{c, items};

    branch.reduction();
    solution = branch.getDistribution();
    LB = branch.lowerBound2();
    _UB.store(branch.upperBound(solution));


    if (_UB == LB) {
        organize();
        foundRes.store(true);
    }
    LB = branch.lowerBound3();
    if (_UB == LB) {
        organize();
        foundRes.store(true);
    }

//    bfs(std::move(branch));
//    threadPool->waitForFinished();
//    organize();
    return branch;
}

void BinPacking::BNB(Branch branch) {
    initThreadPool();
    bfs(std::move(branch));
    waitForFinished();
    endThreadPool();

    sendRequestToMaster();
}

void BinPacking::bfs(Branch branch) {
    ++countBranches;
    //    printf("%d\n",countBranches.load());
    int z = branch.getIndexOfItem();
    std::vector<Item> &items = branch.getItems();
    if (z == items.size() || items[z].weight == 0) return;

    //to all feasible initialized bins
    int j;
    z = branch.getIndexOfItem();
    for (j = z - 1; j >= 0 && !foundRes; --j) {
        if (items[j].weight + items[z].weight <= c) {
            //                int z1 = z;
            Branch newBranch(branch);
            newBranch.mergeTwoItems(j, z);
            newBranch.reduction();
            std::vector<int> curSolution(newBranch.getDistribution());
            int LB_current = newBranch.lowerBound2();
            int UB_current = newBranch.upperBound(curSolution);

            if (UB_current == LB) {
                solution = std::move(curSolution);
                _UB.store(UB_current);
                foundRes.store(true);
                clearQueue();
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
                if (newBranch.getIndexOfItem() + newBranch.getReduced() < UB) {
                    if (newBranch.lowerBound3() < UB) {
                        append(std::move(newBranch));
                    }
                }
            }

        }
    }

    //create a new bin
    if (z + branch.getReduced() < _UB) {
        Branch newBranch(branch);
        //        newBranch->addCurrentItem();
        newBranch.incrementIndex();
        newBranch.reduction();

        std::vector<int> curSolution(newBranch.getDistribution());
        int LB_current = newBranch.lowerBound2();
        int UB_current = newBranch.upperBound(curSolution);

        if (UB_current == LB) {
            solution = std::move(curSolution);
            _UB.store(UB_current);
            foundRes.store(true);
            clearQueue();
            //            delete newBranch;
            //            delete branch;
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

            if (newBranch.getIndexOfItem() + newBranch.getReduced() < UB) {
                if (newBranch.lowerBound3() < UB) {
                    append(std::move(newBranch));
                }
            }
        }

    }
    //    delete branch;
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