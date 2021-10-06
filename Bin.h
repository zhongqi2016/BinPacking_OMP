//
// Created by 吴中奇 on 2021/8/23.
//

#ifndef BINPACKING_BNB_BIN_H
#define BINPACKING_BNB_BIN_H

#include <list>
#include <vector>
#include "Bin.h"


struct Bin {
    int sum;
    std::list<int> serial;
};

Bin initBin(int sum, std::list<int> serial);

std::list<Bin> refactor(const std::vector<int> &items);

void binSort(std::vector<Bin> &binList);

//Bin1 <- Bin2
void mergeBin(std::list<Bin> &w, std::list<Bin>::iterator bin1, std::list<Bin>::iterator bin2);

void mergeSerial(Bin &bin1, Bin &bin2);

void binOrganize(std::vector<Bin> &binList, std::vector<int> &items);

void bin_print(std::vector<Bin> &binList);
void bin_print(std::list<Bin> &binList);
void copySerial(Bin &bin1, Bin &bin2);

int binUsed(std::vector<Bin> &binList, int z);

#endif //BINPACKING_BNB_BIN_H
