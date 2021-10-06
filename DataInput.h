
#ifndef BINPACKING_BNB_DATA_H
#define BINPACKING_BNB_DATA_H

#include "Bin.h"

struct DataInput {
    int n;
    int c;
    std::vector<int> w;
    DataInput(){};
    DataInput(int _n, int _c, std::vector<int> _w) : n(_n), c(_c), w(_w) {};
};

struct DataForCalc {
    std::list<Bin> current;
    int z;
    int z_reduction;
    DataForCalc(){};
    DataForCalc(std::list<Bin> *_current,int _z,int _z_reduction):current(*_current),z(_z),z_reduction(_z_reduction){};
};
/*
DataInput initData(int n, int c, std::vector<int> w);

DataForCalc initData2(std::list<Bin> *current, int z, int z_reduction);
*/
#endif //BINPACKING_BNB_DATA_H

