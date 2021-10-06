
#include <cstdio>
#include "UpperBound.h"


int bestFit( std::list<Bin> &items, int c,std::vector<Bin> &solution) {
    //    bin_print(items);
    int result = 0;
    solution.clear();

    for (auto it=items.begin();it!=items.end();++it) {
        int it_sum=it->sum;
        if (it_sum==0) break;
        int j=0;
        int min = c + 1;
        int bin_min = 0;
        for (; j < result; ++j) {
            if ((solution[j].sum >= it_sum) && (solution[j].sum - it_sum < min)) {
                min = solution[j].sum - it_sum;
                bin_min = j;
            }
        }
        if (min == c + 1) {
            Bin bin;
            bin.sum=c - it_sum;
            copySerial(bin,*it);
            solution.emplace_back(bin);
            ++result;
        } else {
            solution[bin_min].sum -= it_sum;
            copySerial(solution[bin_min], *it);
        }
    }
    //    printf("res= %d, real= %d\n",result, binUsed(_solution));
    return result;
}


//int firstFit(vector<int> w1, int index) {
//    int result = 0;
//    int length1 = w1.size();
//
//    int ava[n];
//
//    for (int i = 0; i < length1; ++i) {
//        int j;
//        for (j = 0; j < result; ++j) {
//            if (ava[j] >= w1[i]) {
//                ava[j] -= w1[i];
//                break;
//            }
//        }
//        if (j == result) {
//            ava[result] = c - w1[i];
//            result++;
//        }
//    }
//    for (int i = index; i < n; ++i) {
//        int j;
//        for (j = 0; j < result; ++j) {
//            if (ava[j] >= items[i]) {
//                ava[j] -= items[i];
//                break;
//            }
//        }
//        if (j == result) {
//            ava[result] = c - items[i];
//            result++;
//        }
//    }
//    return result;
//}