
#include "LowerBound.h"



int L2withA(int alpha,const std::vector<Bin> &w, int c) {
    int J1 = 0;
    int J2 = 0;
    int J3 = 0;
    int sumJ3 = 0;
    int sumJ2 = 0;
    int length = int(w.size());
    for (int i = 0; i < length; i++) {
        if (w[i].sum != 0) {
            if (w[i].sum > c - alpha) {
                J1++;
            } else if (w[i].sum > c / 2) {
                J2++;
                sumJ2 += w[i].sum;
            } else if (w[i].sum >= alpha) {
                J3++;
                sumJ3 += w[i].sum;
            }
        }
    }

    int L = J1 + J2 + (std::max<int>(0, sumJ3 - (J2 * c - sumJ2)) + c - 1) / c;
    return L;
}


int lowerBound2(const std::vector<Bin> &w1, int c) {
    int max = 0;
    int L;

    for (int a = 0; a <= c / 2; a++) {
        L = L2withA(a, w1, c);
        if (L > max) {
            max = L;
        }
    }
    return max;
}


int findLargestK(const std::vector<Bin> &w, int index, int c) {
    int sum = w[index].sum;
    int k = 0;

    for (int i = int(w.size()) - 1; i > 0; --i) {
        if (w[i].sum == 0 || i == index) continue;
        if (sum + w[i].sum <= c) {
            sum += w[i].sum;
            ++k;
        } else {
            break;
        }
    }
    return k;
}

int findMinH(const std::vector<Bin> &w, int index, int c) {
    int wj = w[index].sum;
    for (int i = 0; i < w.size(); ++i) {
        if (w[i].sum == 0 || i == index) continue;
        if (wj + w[i].sum <= c) {
            return i;
        }
    }
    //fail
    return -1;
}

bool findAB(const std::vector<Bin> &w, int index, int &a, int &b, int c) {
    int ava = c - w[index].sum;
    int i;
    int maxValue = 0;
    bool flag = false;
    for (i = 0; i < w.size(); ++i) {
        if (w[i].sum == 0 || i == index) continue;
        if (ava > w[i].sum) {
            for (int j = i + 1; j < w.size(); ++j) {
                if (w[j].sum == 0 || j == index) continue;
                if (w[i].sum + w[j].sum == ava) {
                    a = i;
                    b = j;
                    return true;
                }
                if (w[i].sum + w[j].sum < ava) {
                    if (w[i].sum + w[j].sum > maxValue) {
                        maxValue = w[i].sum + w[j].sum;
                        a = i;
                        b = j;
                        flag = true;
                    }
                    break;
                }
            }
        }
    }
    return flag;
}

int getPrevious(std::vector<Bin> &w, int currentNode, int num) {
    int i;
    for (i = currentNode - 1; i >= 0 && num > 0; --i) {
        if (w[i].sum > 0) {
            --num;
        }
    }
    return i;
}

int getDistance(std::vector<Bin> &w, int a, int b) {
    if (b < a) {
        printf("error");
        return -1;
    }//error
    int distance = 1;
    for (int i = a + 1; i < b; ++i) {
        if (w[i].sum > 0) ++distance;
    }
    return distance;
}

int reduction(std::vector<Bin> &w, int &z, int c) {
//    std::vector<int> w(w1);
//    w.reserve(n);
//    w.insert(w.end(), items.begin() + index, items.end());
    std::vector<int> bj(w.size(), 0);
    int zr = 0;
    std::vector<int> F;
    int count = 0;//Deleted items that have been put in bins
    int reduced = 0;
    for (int i = 0; i < w.size(); ++i) {
        if (w[i].sum == 0) continue;
        int k = findLargestK(w, i, c);
        F.clear();
        if (k == 0) {
            F.emplace_back(i);
        } else {
            int h = findMinH(w, i, c);
            if (h == -1) continue;
            if (k == 1 || w[i].sum + w[h].sum == c) {
                F.emplace_back(i);
                F.emplace_back(h);
            } else if (k == 2) {
                int a;
                int b;
                if (findAB(w, i, a, b, c)) {
                    if (w[h].sum >= w[a].sum + w[b].sum) {
                        F.emplace_back(i);
                        F.emplace_back(h);
                    } else if (w[h].sum == w[a].sum && (getDistance(w, a, b) <= 2
                                                        || w[i].sum + w[getPrevious(w, b, 1)].sum +
                                                           w[getPrevious(w, b, 2)].sum > c)) {
                        F.emplace_back(i);
                        F.emplace_back(a);
                        F.emplace_back(b);
                    }
                }
            }
        }
        if (!F.empty()) {
            ++zr;
            int sum = 0;

            if (z > 0) ++count;
            for (int j = 1; j < F.size(); ++j) {

                mergeBin(w[F[0]], w[F[j]]);
                bj[F[j]] = zr;
//                printf("%d ",w[j]);
                w[F[j]].sum = 0;
                ++reduced;
                if (j < z) ++count;
            }
            w[F[0]].sum = 0;

        }
//        binSort(w);
    }
//    z -= count;

    return zr;
}

int lowerBound3(const std::vector<Bin> &w1, int c) {
    std::vector<Bin> w(w1);
    int n = w.size();
    int L3 = 0;
    int L2;
    int z = 0;
    int z1 = 0;

    while (n >= 1) {
        z += reduction(w, z1, c);
        n = w.size();
        if (n == 0) L2 = 0;
        else L2 = lowerBound2(w, c);
        L3 = std::max(L3, z + L2);
        if (n > 0) {
            n = n - 1;
            w.pop_back();
        }
    }

    return L3;
}

