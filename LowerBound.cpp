
#include "LowerBound.h"

int L2withA(int alpha, const std::list<Bin> &w, int c) {
    int J1 = 0;
    int J2 = 0;
    int J3 = 0;
    int sumJ3 = 0;
    int sumJ2 = 0;
    for (auto &item:w) {
        if (item.sum != 0) {
            if (item.sum > c - alpha) {
                J1++;
            } else if (item.sum > c / 2) {
                J2++;
                sumJ2 += item.sum;
            } else if (item.sum >= alpha) {
                J3++;
                sumJ3 += item.sum;
            }
        }
    }

    int L = J1 + J2 + (std::max<int>(0, sumJ3 - (J2 * c - sumJ2)) + c - 1) / c;
    return L;
}


int lowerBound2(const std::list<Bin> &w1, int c) {
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


int findLargestK(std::list<Bin> &w, std::list<Bin>::iterator index, int c) {
    int sum = index->sum;
    int k = 0;

    for (auto it = w.end(); it != w.begin();) {
        --it;
        if (it->sum == 0 || it == index) continue;
        if (sum + it->sum <= c) {
            sum += it->sum;
            ++k;
        } else {
            break;
        }
    }
    return k;
}

std::list<Bin>::iterator findMinH(std::list<Bin> &w, std::list<Bin>::iterator index, int c) {
    for (auto it = w.begin(); it != w.end(); ++it) {
        if (it->sum == 0 || it == index) continue;
        if (index->sum + it->sum <= c) {
            return it;
        }
    }
    //fail
    return w.end();
}

bool findAB(std::list<Bin> &w, std::list<Bin>::iterator index, std::list<Bin>::iterator &a, std::list<Bin>::iterator &b,
            int c) {
    int ava = c - index->sum;
    int maxValue = 0;
    bool flag = false;
    auto iterator_j = w.begin();
    while (iterator_j->sum != 0&&iterator_j!=w.end()) {
        ++iterator_j;
    }
    for (auto iterator_i = w.begin(); iterator_i != w.end(); ++iterator_i) {
        int i_sum = iterator_i->sum;
        if (i_sum == 0 || iterator_i == index) continue;
        if (i_sum >= ava) continue;
        else {
            --iterator_j;
            while (iterator_j != iterator_i) {
                //                printf("%d\n",iterator_j->sum);
                if (iterator_j==index){--iterator_j; continue;}
                if (iterator_j->sum + i_sum == ava) {
                    a = iterator_i;
                    b = iterator_j;
                    return true;
                } else if (iterator_j->sum + i_sum < ava) {
                    if (iterator_j->sum + i_sum > maxValue) {
                        maxValue = iterator_j->sum + i_sum;
                        a = iterator_i;
                        b = iterator_j;
                        flag = true;
                    }
                    --iterator_j;
                } else break;

            }
            break;
        }
    }
    return flag;
}





int reduction(std::list<Bin> &w, int &z, int c) {
    int zr = 0;
    std::vector<std::list<Bin>::iterator> F;
    int count = 0;//Deleted items that have been put in bins
    int reduced = 0;

    for (auto it = w.begin(); it != w.end(); ++it) {
        if (it->sum == 0) break;
        int k = findLargestK(w, it, c);
        F.clear();
        if (k == 0) {
            F.emplace_back(it);
        } else {
            auto h = findMinH(w, it, c);
            if (h == w.end()) continue;
            if (k == 1 || it->sum + h->sum == c) {
                F.emplace_back(it);
                F.emplace_back(h);
            } else if (k == 2) {
                auto a = w.begin();
                auto b = w.begin();
                if (findAB(w, it, a, b, c)) {
                    if (h->sum >= a->sum + b->sum) {
                        F.emplace_back(it);
                        F.emplace_back(h);
                    } else if (h->sum == a->sum) {
                        int distance = std::distance(a, b);
                        auto bl=b;
                        --bl;
                        int bl1 = bl->sum;
                        --bl;
                        int bl2 = bl->sum;
                        if (distance <= 2 || (it->sum + bl1 + bl2 > c)) {
                            F.emplace_back(it);
                            F.emplace_back(a);
                            F.emplace_back(b);
                        }
                    }
                }
            }
        }
        if (!F.empty()) {
            ++zr;

            //создать один новый контейнер
            Bin newBin;
            newBin.sum = 0;
            std::list<int> serial;
            newBin.serial = serial;

            //Добавить объекты массива F в новый контейнер
            int ss = 0;
            for (auto j:F) {
                if (std::distance(w.begin(),j) < z) ++count;
                ss += j->sum;
                newBin.serial.splice(newBin.serial.end(), j->serial);
                if (j == it) ++it;
                w.erase(j);
                ++reduced;

            }

            w.emplace_back(newBin);
        }
    }
    z -= count;
    return zr;
}

int L2withA(int alpha, const std::vector<int> &w, int c) {
    int J1 = 0;
    int J2 = 0;
    int J3 = 0;
    int sumJ3 = 0;
    int sumJ2 = 0;
    int length = int(w.size());
    for (int i = 0; i < length; i++) {
        if (w[i] != 0) {
            if (w[i] > c - alpha) {
                J1++;
            } else if (w[i] > c / 2) {
                J2++;
                sumJ2 += w[i];
            } else if (w[i] >= alpha) {
                J3++;
                sumJ3 += w[i];
            }
        }
    }

    int L = J1 + J2 + (std::max<int>(0, sumJ3 - (J2 * c - sumJ2)) + c - 1) / c;
    return L;
}


int lowerBound2(const std::vector<int> &w1, int c) {
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


int findLargestK(const std::vector<int> &w, int index, int c) {
    int sum = w[index];
    int k = 0;


    for (int i = int(w.size()) - 1; i > 0; --i) {
        if (w[i] == 0 || i == index) continue;
        if (sum + w[i] <= c) {
            sum += w[i];
            ++k;
        } else {
            break;
        }
    }
    return k;
}

int findMinH(const std::vector<int> &w, int index, int c) {
    int wj = w[index];
    for (int i = 0; i < w.size(); ++i) {
        if (w[i] == 0 || i == index) continue;
        if (wj + w[i] <= c) {
            return i;
        }
    }
    //fail
    return -1;
}

bool findAB(const std::vector<int> &w, int index, int &a, int &b, int c) {
    int ava = c - w[index];
    int i;
    int maxValue = 0;
    bool flag = false;
    for (i = 0; i < w.size(); ++i) {
        if (w[i] == 0 || i == index) continue;
        if (ava > w[i]) {
            for (int j = i + 1; j < w.size(); ++j) {
                if (w[j] == 0 || j == index) continue;
                if (w[i] + w[j] == ava) {
                    a = i;
                    b = j;
                    return true;
                }
                if (w[i] + w[j] < ava) {
                    if (w[i] + w[j] > maxValue) {
                        maxValue = w[i] + w[j];
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

int reductionForL3(std::vector<int> &w, int &z, int c) {
    //    std::vector<int> w(w1);
    //    w.reserve(n);
    //    w.insert(w.end(), items.begin() + index, items.end());
    std::vector<int> bj(w.size(), 0);
    int zr = 0;
    std::vector<int> F;
    int count = 0;//Deleted items that have been put in bins
    int reduced = 0;
    for (int i = 0; i < w.size(); ++i) {
        if (w[i] == 0) continue;
        int k = findLargestK(w, i, c);
        F.clear();
        if (k == 0) {
            F.emplace_back(i);
        } else {
            int h = findMinH(w, i, c);
            if (h == -1) continue;
            if (k == 1 || w[i] + w[h] == c) {
                F.emplace_back(i);
                F.emplace_back(h);
            } else if (k == 2) {
                int a;
                int b;
                if (findAB(w, i, a, b, c)) {
                    if (w[h] >= w[a] + w[b]) {
                        F.emplace_back(i);
                        F.emplace_back(h);
                    } else if (w[h] == w[a] && (b - a <= 2 || w[i] + w[b - 1] + w[b - 2] > c)) {
                        F.emplace_back(i);
                        F.emplace_back(a);
                        F.emplace_back(b);
                    }
                }
            }
        }
        if (!F.empty()) {
            ++zr;
            for (int j : F) {
                bj[j] = zr;
                //                printf("%d ",w[j]);
                w[j] = 0;
                reduced++;
                if (j < z) ++count;

            }
            //            printf("\n");
            //            reduced += int(F.size());
        }

    }
    z -= count;
    sort(w.rbegin(), w.rend());
    if (w[w.size() - reduced] == 0) {
        w.resize(w.size() - reduced);
    }
    return zr;
}


int lowerBound3(const std::list<Bin> &w1, int c) {
    std::vector<int> w;
    w.reserve(w1.size());
    for (auto item:w1) {
        if (item.sum != 0)
            w.emplace_back(item.sum);
        else break;
    }
    int n = w.size();
    int L3 = 0;
    int L2;
    int z = 0;
    int z1 = 0;

    while (n >= 1) {
        z += reductionForL3(w, z1, c);
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

