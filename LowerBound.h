#ifndef BINPACKING_BNB_LOWERBOUND_H
#define BINPACKING_BNB_LOWERBOUND_H

#include "Bin.h"
#include <algorithm>

/// @param w1 - super items

int lowerBound2(const std::list<Bin> &w1, int c);

int lowerBound3(const std::list<Bin> &w1, int c);

//Reduction Algorithm(MTRP)
int reduction(std::list<Bin> &w, int &z, int c);


#endif //BINPACKING_BNB_LOWERBOUND_H

