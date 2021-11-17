#include <iostream>
#include "ReadFiles.h"


using namespace std;



int main() {
    int num_threads=8;
    string path = "./bin1data/"; //Path of data

    omp_set_num_threads(num_threads);
    ReadFiles readFiles(path);
    for (int i = 0; i < readFiles.getNumOfFiles(); ++i) {
        std::cout << i << ". filename: " << readFiles.getFileName(i) << std::endl;

        BinPacking binPacking = readFiles.getData(i);
        double start, end;
        start = omp_get_wtime();
        int result = binPacking.BNB();
        end = omp_get_wtime();
        double time =  (end - start);
        binPacking.printSolution();
        printf("Number of bins needed = %d\nTime=%lf\n", result, time);
    }

    return 0;
}
