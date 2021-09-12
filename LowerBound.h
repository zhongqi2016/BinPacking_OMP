#ifndef BINPACKING_BNB_LOWERBOUND_H
#define BINPACKING_BNB_LOWERBOUND_H

#include "Bin.h"
#include <algorithm>

/// @param w1 - super items

int lowerBound2(const std::vector<Bin> &w1, int c);

int lowerBound3(const std::vector<Bin> &w1, int c);

//Reduction Algorithm(MTRP)
int reduction(std::vector<Bin> &w, int &z, int c);


#endif //BINPACKING_BNB_LOWERBOUND_H

