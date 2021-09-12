
#ifndef BINPACKING_BNB_ALGORITHM_H
#define BINPACKING_BNB_ALGORITHM_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <stack>
#include <omp.h>
#include "UpperBound.h"
#include "LowerBound.h"
#include "DataInput.h"
#include "Bin.h"

int BNB(DataInput data);
#endif //BINPACKING_BNB_ALGORITHM_H

