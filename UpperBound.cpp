
#include <cstdio>
#include "UpperBound.h"


int firstFit( std::vector<Bin> &items, int c) {
    int result = 0;
    int length = items.size();
    int ava[length];

    for (int i = 0; i < length; ++i) {
        int j;
        for (j = 0; j < result; ++j) {
            if (ava[j] >= items[i].sum) {
                ava[j] -= items[i].sum;
                mergeBin(items[j],items[i]);
                break;
            }
        }
        if (j == result) {
            ava[result] = c - items[i].sum;
            result++;
        }
    }
    return result;
}

int bestFit( std::vector<Bin> &items, int c,std::vector<Bin> &solution) {
    int result = 0;
    int length = items.size();
    solution.clear();
    solution.resize(length);
//    int ava[length];

    for (int i = 0; i < length; ++i) {
        if (items[i].sum<=0) continue;
        int j;
        int min = c + 1;
        int bin_min = 0;
        for (j = 0; j < result; j++) {
            if (solution[j].sum >= items[i].sum && solution[j].sum - items[i].sum < min) {
                min = solution[j].sum - items[i].sum;
                bin_min = j;
            }
        }
        if (min == c + 1) {
            solution[result].sum = c - items[i].sum;
            copySerial(solution[result],items[i]);
            ++result;
        } else {
            solution[bin_min].sum -= items[i].sum;
            copySerial(solution[bin_min], items[i]);
        }
    }
//    bin_print(solution);
//    printf("res= %d, real= %d\n",result, binUsed(solution));
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