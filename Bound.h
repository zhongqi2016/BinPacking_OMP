//
// Created by 吴中奇 on 2021/11/1.
//

#ifndef BINPACKING_BNB_BOUND_H
#define BINPACKING_BNB_BOUND_H

#include <vector>
#include <climits>
#include <unordered_map>
#include "Item.h"

class Bound {
public:
    Bound(int _c, std::vector<Item> &_items) : c(_c), items(_items), indexOfItem(0),
                                               reduced(0),
                                               distribution(std::vector<int>(_items.size(), 0)) {}

    int lowerBound2() const;

    int lowerBound3() const;

    void reduction();

    int upperBound(std::vector<int> &currSolution);

    void mergeTwoItems(int index1, int index2);

    std::vector<int> &getDistribution() { return distribution; }

    int getIndexOfItem() { return indexOfItem; }

    void incrementIndex() {
        ++indexOfItem;
//        while (items[indexOfItem].weight + items[indexOfItem].weight > c) {
//            ++indexOfItem;
//        }
    }

    int getReduced() { return reduced; }

    std::vector<Item> &getItems() { return items; }

    void addCurrentItem();

private:
    int c;//capacity
    int reduced;
    int indexOfItem;

    std::vector<Item> items;
    std::vector<int> distribution;
    //if distribution==0 -> not distributed this item
    //If not equal to zero, this number is the index of bin
//    std::vector<std::vector<int>*> bins;

    int L2withA(int alpha) const;

    int findLargestK(int index) const;

    int findMinH(int index) const;

    bool findAB(int index, int &a, int &b) const;

    void printDistribution() const;
};

#endif //BINPACKING_BNB_BOUND_H
