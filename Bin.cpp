//
// Created by 吴中奇 on 2021/8/23.
//
#include <cstdio>
#include "Bin.h"

Bin initBin(int sum, std::list<int> serial) {
    Bin bin;
    bin.sum = sum;
    bin.serial = std::move(serial);
    return bin;
}


std::list<Bin> refactor(const std::vector<int> &items) {
    int length = items.size();
    std::list<Bin> list;

    for (int i = 0; i < length; ++i) {
        std::list<int> itemsInBin;
        itemsInBin.emplace_back(i);
        Bin bin = initBin(items[i], itemsInBin);

        list.emplace_back(bin);
    }
    return list;
}

bool cmp(const Bin &a, const Bin &b) {
    return a.sum > b.sum;
}

void binSort(std::vector<Bin> &binList) {
    std::sort(binList.begin(), binList.end(), cmp);
}

Bin binCombine(std::list<Bin>::iterator bin1, std::list<Bin>::iterator bin2) {
    std::list<int> list;
    list.splice(list.begin(), bin1->serial);
    list.splice(list.end(),bin2->serial);
    Bin bin;
    bin.sum= bin1->sum + bin2->sum;
    bin.serial=list;
    return bin;
}

//Bin1 <- Bin2
void mergeBin(std::list<Bin> &w, std::list<Bin>::iterator bin1, std::list<Bin>::iterator bin2) {
    Bin newBin;
    newBin.sum=bin1->sum+bin2->sum;
    newBin.serial.splice(newBin.serial.end(), bin1->serial);
    newBin.serial.splice(newBin.serial.end(), bin2->serial);
    w.erase(bin1);
    w.erase(bin2);
    for (auto it_w=w.begin();it_w!=w.end();++it_w) {
        if(it_w->sum<newBin.sum){
            w.insert(it_w, std::move(newBin));
            break;
        }
    }
}



void copySerial(Bin &bin1, Bin &bin2) {
    std::list<int>::iterator it;
    for (it = bin2.serial.begin(); it != bin2.serial.end(); ++it) {
        bin1.serial.push_back(*it);
    }
}

void binOrganize(std::vector<Bin> &binList, std::vector<int> &items) {
    int count = 0;
    for (int i = 0; i < binList.size(); ++i) {
        int sum = 0;
        std::list<int>::iterator it;
        std::list<int> &l = binList[i].serial;
        for (it = l.begin(); it != l.end(); ++it) {
            sum += items[*it];
        }
        if (sum == 0) count++;
        binList[i].sum = std::move(sum);
    }
    binSort(binList);
    binList.resize(binList.size() - count);
}

void bin_print(std::vector<Bin> &binList) {
    for (int i = 0; i < binList.size(); ++i) {
        std::list<int>::iterator it;
        printf("%d(", binList[i].sum);
        std::list<int> &l = binList[i].serial;
        for (it = l.begin(); it != l.end(); ++it) {
            printf("%d, ", *it);
        }
        printf("),");
    }
    printf("\n");
}

void bin_print(std::list<Bin> &binList) {
    for (auto i:binList) {
        std::list<int>::iterator it;
        printf("%d(", i.sum);
        std::list<int> &l = i.serial;
        for (it = l.begin(); it != l.end(); ++it) {
            printf("%d, ", *it);
        }
        printf("),");
    }
    printf("\n");
}

