
#include "Algorithm.h"

int BinPacking::BNB() {
    std::vector<Item> items = refactor(weightOfItems);
    sort(items.rbegin(), items.rend());
    Bound bound(c, items);
    UB = INT_MAX;

    std::stack<Bound> s;
    s.emplace(bound);

#pragma omp parallel
    {
#pragma omp single
        {
            dfs(s);
        }
    }
    organize();
    return UB;
}

void BinPacking::dfs(std::stack<Bound> s) {
//    printf("%d\n",omp_get_thread_num());
    while (!s.empty() && foundRes == false) {
        Bound bound = std::move(s.top());
        s.pop();

        int z = bound.getIndexOfItem();
        std::vector<Item> &items = bound.getItems();
        if (z == items.size() || items[z].weight == 0) return;

        //create a new bin
        if (z < UB - 1) {
            Bound newBound(bound);
            newBound.addCurrentItem();
            newBound.reduction();

            std::vector<int> curSolution(newBound.getDistribution());
            int LB_current = newBound.lowerBound2();
            int UB_current = newBound.upperBound(curSolution);

            if (UB_current == LB) {
                solution = std::move(curSolution);
                UB = UB_current;
                foundRes=true;
                return;

            }
            if (UB > UB_current) {
                UB = UB_current;
                solution = std::move(curSolution);
            }
            newBound.incrementIndex();

            if (UB_current > LB_current && LB_current < UB) {

                if (newBound.getIndexOfItem() + newBound.getReduced() < UB) {
                    if (newBound.lowerBound3() < UB) {
                        s.push(newBound);
                    }
                }

            }

        }

        //to all feasible initialized bins
        int j;
        z = bound.getIndexOfItem();
        for (j = z - 1; j >= 0 && foundRes == false; --j) {
            if (items[j].weight + items[z].weight <= c) {
//                int z1 = z;
                Bound newBound(bound);
                newBound.mergeTwoItems(j, z);
                std::vector<int> curSolution(newBound.getDistribution());

                newBound.reduction();
                int LB_current = newBound.lowerBound2();
                int UB_current = newBound.upperBound(curSolution);

                if (UB_current == LB) {
                    solution = std::move(curSolution);
                    UB = UB_current;
                    foundRes=true;
                    return;
                }
                if (UB > UB_current) {
                    UB = UB_current;
                    solution = std::move(curSolution);
                }

                if (UB_current > LB_current && LB_current < UB) {
                    if (newBound.getIndexOfItem() + newBound.getReduced() < UB) {
                        if (newBound.lowerBound3() < UB) {
                            s.push(newBound);
                        }
                    }
                }

            }
        }

        while (omp_get_max_threads() - num_threads > 0 && s.size() > 1&&foundRes== false) {
#pragma omp atomic update
            ++num_threads;

            auto &data = s.top();
            std::stack<Bound> s2;
            s2.emplace(std::move(data));
            s.pop();
#pragma omp task  firstprivate(s2)  default(shared)
            dfs(s2);
        }

    }
#pragma omp atomic update
    --num_threads;
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

void BinPacking::printSolution() {
    for (auto index: solution) {
        printf("%d ", index);
    }
    printf("\n");
}

/*
void dfs(std::stack<DataForCalc> &s, std::vector<Bin> &solution, int &UB, int LB, int c, int &num_threads, bool &isBreak) {
    std::vector<Bin> *_solution = nullptr;
    std::vector<Bin> solution_UB;
    solution_UB.reserve(UB);
//    bool isBreak = true;
    while (!s.empty() && isBreak) {
        DataForCalc node = s.top();
        s.pop();
        int &z = node.z;
        int &z_reduction = node.z_reduction;
        std::list<Bin> now = node.current;

        auto iterator_z = std::next(now.begin(), z);
        ++iterator_z;
        if (iterator_z->sum == 0) break;

        if (z < UB - 1) {
            int z1 = z;
            ++z1;
            std::list<Bin> current(now);
            int zr = reduction(current, z1, c) + z_reduction;

            int LB_current = lowerBound2(current, c) + zr;
            int UB_current = bestFit(current, c, solution_UB) + zr;

            if (UB_current == LB) {
#pragma omp atomic write
                UB = UB_current;
                _solution = &solution_UB;
                getDetermined(*_solution, current);
#pragma omp atomic write
                isBreak = false;
            }
            if (UB > UB_current) {
#pragma omp atomic write
                UB = UB_current;
                _solution = &solution_UB;
                getDetermined(*_solution, current);
            }
            if (UB_current > LB_current && LB_current < UB) {

                if (z1 + zr < UB) {
                    int L3 = lowerBound3(current, c) + zr;

                    if (L3 < UB) {

                        s.push(DataForCalc(&current, z1, zr));
                    }
                }

            }

        }

        //to all feasible initialized bins
        for (int j = z - 1; j >= 0 && isBreak; --j) {
            std::list<Bin> current(now);
            auto iterator_j = std::next(current.begin(), j);
            auto iterator_i = std::next(iterator_j, z - j);

            if (iterator_i->sum == 0) break;
            if (iterator_j->sum + iterator_i->sum <= c) {
                int z1 = z;
                mergeBin(current, iterator_i, iterator_j);
                --z1;
                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
                solution_UB.clear();
                int UB_current = bestFit(current, c, solution_UB) + zr;

                if (UB_current == LB) {
#pragma omp atomic write
                    UB = UB_current;
                    _solution = &solution_UB;
                    getDetermined(*_solution, current);
#pragma omp atomic write
                    isBreak = false;
                    //                    return UB_current;
                }
                if (UB > UB_current) {
#pragma omp atomic write
                    UB = UB_current;
                    _solution = &solution_UB;
                    getDetermined(*_solution, current);
                }
                if (UB_current > LB_current && LB_current < UB) {
                    if (z1 + zr < UB) {
                        int L3 = lowerBound3(current, c) + zr;
                        if (L3 < UB) {
                            s.push(DataForCalc(&current, z1, zr));
                        }
                    }
                }
            }


        }

        while (omp_get_max_threads() - num_threads > 0 && s.size() > 1) {
            DataForCalc data = s.top();
            std::stack<DataForCalc> s2;
            s2.push(std::move(data));
            s.pop();
#pragma omp task  shared(UB, num_threads, solution, isBreak) firstprivate(s2, c, LB)  default(none)
            dfs(s2, solution, UB, LB, c, num_threads, isBreak);

#pragma omp atomic update
            ++num_threads;
        }
    }
    if (_solution) {
        solution=move(*_solution);
    }
#pragma omp atomic update
    --num_threads;
}


int BNB(DataInput data) {
    std::vector<Bin> *solution = NULL;
    std::vector<int> &items = data.w;
    std::sort(items.rbegin(), items.rend());
    std::list<Bin> binList = refactor(items);
    //    bin_print(binList);
    int c = data.c;

    int LB = lowerBound2(binList, c);
    std::vector<Bin> solution_UB;
    solution = &solution_UB;
    int UB = bestFit(binList, c, solution_UB);
    if (LB == UB) {
        binOrganize(solution_UB, items);
        solution = &solution_UB;
        bin_print(*solution);
        return LB;
    }
    int L3 = lowerBound3(binList, c);

    if (L3 == UB) {
        binOrganize(solution_UB, items);
        solution = &solution_UB;
        bin_print(*solution);
        return L3;
    }
    int z = 0;
    int z_res = reduction(binList, z, c);

    std::stack<DataForCalc> s;
    s.push(DataForCalc(&binList, z, z_res));
    int num_thread = 1;
#pragma omp parallel
    {
#pragma omp single
        {
            bool isBreak = true;
            dfs(s, *solution, UB, L3, c, num_thread, isBreak);
        }
    }

    binOrganize(*solution, items);
    bin_print(*solution);
    return solution->size();
}

*/