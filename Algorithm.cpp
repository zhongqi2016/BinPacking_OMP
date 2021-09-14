
#include "Algorithm.h"

void getDetermined(std::vector<Bin> &solution, std::vector<Bin> &current) {
    for (auto &i : current) {
        if (i.sum == 0 && !i.serial.empty()) {
            solution.emplace_back(i);
        }
    }
}

void skipDetermined(std::vector<Bin> &w, int &z) {
    for (; z < w.size(); ++z) {
        if (w[z].sum != 0) break;
    }
}


void calc(std::stack<DataForCalc> &s, std::vector<Bin> &solution, int &UB, int LB, int c, int &num_threads) {
    std::vector<Bin> *_solution = NULL;
    std::vector<Bin> solution_UB;
    bool isBreak = true;
    printf("id:%d\n", omp_get_thread_num());
    while (!s.empty() && isBreak) {
        if (UB == LB) isBreak = false;
        DataForCalc node = s.top();
        s.pop();
        int &z = node.z;
        int &z_reduction = node.z_reduction;
        std::vector<Bin> &now = node.current;
        skipDetermined(now, ++z);
        if (z == now.size() || now[z].sum == 0) isBreak = false;
        int i = z;
        //create a new bin

        if (z < UB - 1) {
            int z1 = z;
            std::vector<Bin> current(now);
//            binSort(current);
//            skipDetermined(current,++z1);
            int zr = reduction(current, z1, c) + z_reduction;

            int LB_current = lowerBound2(current, c) + zr;
//            std::vector<Bin> solution_UB;
            int UB_current = bestFit(current, c, solution_UB) + zr;

            if (UB_current == LB) {
#pragma omp atomic write
                UB = UB_current;
                delete _solution;
                _solution = &solution_UB;
                getDetermined(*_solution, current);
                isBreak = false;
            }
            if (UB > UB_current) {
#pragma omp atomic write
                UB = UB_current;
                delete _solution;
                _solution = &solution_UB;
                getDetermined(*_solution, current);
            }
            if (UB_current > LB_current && LB_current < UB) {

                if (binUsed(current, z1) + zr < UB) {
                    int L3 = lowerBound3(current, c) + zr;

                    if (L3 < UB) {

                        s.push(initData2(current, z1, zr));
                    }
                }

            }

        }

        //to all feasible initialized bins
        int j;
        for (j = z - 1; j >= 0 && isBreak; --j) {

            if (now[j].sum == 0) continue;
            if (now[j].sum + now[i].sum <= c) {
                int z1 = z;
                std::vector<Bin> current(now);
//                printf("%d:%d<-%d:%d\n",j,current[j].sum,i,current[i].sum);
                mergeBin(current[j], current[i]);

                int zr = reduction(current, z1, c) + z_reduction;
                int LB_current = lowerBound2(current, c) + zr;
//                std::vector<Bin> solution_UB;
                int UB_current = bestFit(current, c, solution_UB) + zr;

                if (UB_current == LB) {
#pragma omp atomic write
                    UB = UB_current;
                    delete _solution;
                    _solution = &solution_UB;
                    getDetermined(*_solution, current);
                    isBreak = false;
//                    return UB_current;
                }
                if (UB > UB_current) {
#pragma omp atomic write
                    UB = UB_current;
                    delete _solution;
                    _solution = &solution_UB;
                    getDetermined(*_solution, current);
                }
                if (UB_current > LB_current && LB_current < UB) {
                    if (binUsed(current, z1) + zr < UB) {
                        int L3 = lowerBound3(current, c) + zr;
                        if (L3 < UB) {

                            s.push(initData2(current, z1, zr));
                        }
                    }
                }
            }


        }

//        printf("%d\n", omp_get_num_threads());
        while (omp_get_max_threads() - num_threads > 0 && s.size() > 1) {
//            printf("o %d\n",omp_get_max_threads() - num_threads);
            DataForCalc data = s.top();
            std::stack<DataForCalc> s2;
            s2.push(std::move(data));
            s.pop();
#pragma omp task  shared(UB, num_threads, solution) firstprivate(s2, c, LB)  default(none)
            calc(s2, solution, UB, LB, c, num_threads);

#pragma omp atomic update
            ++num_threads;
        }
    }
    if (_solution) {
        solution.swap(*_solution);
    }
#pragma omp atomic update
    --num_threads;
}


int BNB(DataInput data) {
    omp_set_nested(1);
    std::vector<Bin> *solution = NULL;
    std::vector<int> &items = data.w;
    std::vector<Bin> binList = refactor(items);
    binSort(binList);
//    bin_print(binList);
    int c = data.c;

    int LB = lowerBound2(binList, c);
    std::vector<Bin> solution_UB;

    int UB = bestFit(binList, c, solution_UB);
    binOrganize(solution_UB, items);
    solution = &solution_UB;

    if (LB == UB) {
        bin_print(*solution);
        return LB;
    }
    int L3 = lowerBound3(binList, c);

    if (L3 == UB) {
        bin_print(*solution);
        return L3;
    }
    int z = 0;
//    std::vector<Bin> determined(UB);
    int z_res = reduction(binList, z, c);
    std::stack<DataForCalc> s;
    s.push(initData2(binList, z, z_res));
//    std::vector<Bin> res_calc;

    int num_thread = 1;
#pragma omp parallel num_threads(8)
    {
#pragma omp single
        {
            printf("%d\n", omp_get_num_procs());
            calc(s, *solution, UB, L3, c, num_thread);
        }
    }
//    if (solution->size() == 0) {
//        solution = &solution_UB;
//    }
    binOrganize(*solution, items);
    bin_print(*solution);
    return solution->size();
}

