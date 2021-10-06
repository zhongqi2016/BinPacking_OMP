#ifndef BINPACKING_BNB_UPPERBOUND_H
#define BINPACKING_BNB_UPPERBOUND_H

#include "Bin.h"

//int firstFit( std::vector<Bin> &items, int c);

int bestFit( std::list<Bin> &items, int c,std::vector<Bin> &solution);
/// @param items - super items
/// @return - Minimize number of used Bins

#endif //BINPACKING_BNB_UPPERBOUND_H


