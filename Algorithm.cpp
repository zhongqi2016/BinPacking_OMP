
#include "Algorithm.h"

void getDetermined(std::vector<Bin> &solution, std::list<Bin> &current) {
    for (auto it = current.rbegin(); it != current.rend(); ++it) {
        if (it->sum == 0 && it->serial.size() != 0) {
            solution.emplace_back(*it);
        } else break;
    }
}


void
calc(std::stack<DataForCalc> &s, std::vector<Bin> &solution, int &UB, int LB, int c, int &num_threads, bool &isBreak) {
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
            calc(s2, solution, UB, LB, c, num_threads, isBreak);

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
    int c = data.c;

    int LB = lowerBound2(binList, c);
    std::vector<Bin> solution_UB;
    solution=&solution_UB;
    int UB = bestFit(binList, c, solution_UB);
    if (LB == UB) {
        binOrganize(solution_UB, items);
        solution = &solution_UB;
//        bin_print(*solution);
        return LB;
    }
    int L3 = lowerBound3(binList, c);

    if (L3 == UB) {
        binOrganize(solution_UB, items);
        solution = &solution_UB;
//        bin_print(*solution);
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
            bool isBreak=true;
            calc(s,*solution, UB, L3, c,num_thread,isBreak);
        }
    }

    binOrganize(*solution, items);
//    bin_print(*solution);
    return solution->size();
}

