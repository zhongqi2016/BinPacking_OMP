#include <iostream>
#include "ReadFiles.h"


using namespace std;


int main() {
    string path = "./bin1data/"; //Path of data
    //The number of threads to be tested
    const array<int, 4> threads = {2};

    ReadFiles readFiles(path);
    readFiles.sortDirs();

    for (int i = 0; i < readFiles.getNumOfFiles(); ++i) {
        cout << i << ". " << readFiles.getFileName(i);
        BinPacking binPacking = readFiles.getData(i);
        int result = -1;
        for (auto th:threads) {
            omp_set_num_threads(th);
            double start, end;
            start = omp_get_wtime();

            int res = binPacking.BNB();
            int countBranches = binPacking.getCountBranches();
            end = omp_get_wtime();
            double time = (end - start);

            if (result == -1) {
                result = res;
            } else if (result != res) {
                printf(" error!");
            }
//            cout<<"solution: ";
//            binPacking.printSolution2();
            printf(" %lf %d", time, countBranches);
        }
        printf(" %d\n",result);
    }

    return 0;
}
