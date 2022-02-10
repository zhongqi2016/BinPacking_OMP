#include <iostream>
#include "ReadFiles.h"


using namespace std;


int main() {
    int num_threads = 8; //Set number of threads
    string path = "./bin1data/"; //Path of data

    omp_set_num_threads(num_threads);
    ReadFiles readFiles(path);
    readFiles.sortDirs();
    for (int i = 0; i < readFiles.getNumOfFiles(); ++i) {
        cout << i << ". " << readFiles.getFileName(i)<<endl;
        BinPacking binPacking = readFiles.getData(i);
        double start, end;
        start = omp_get_wtime();

        int result = binPacking.BNB();
        int countBranches=binPacking.getCountBranches();
        end = omp_get_wtime();
        double time = (end - start);
        cout<<"solution: ";
        binPacking.printSolution2();
        printf("result=%d, time=%lf, branches=%d\n", result,time,countBranches);

    }

    return 0;
}
