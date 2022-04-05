#include <iostream>
#include "ReadFiles.h"


using namespace std;


void getResponse(int numThreads) {
    int command[2];
    bool run = true;
    bool stop = false;
    while (!stop) {
        int command[2];
        MPI_Bcast(command, 2, MPI_INT, id_root, MPI_COMM_WORLD);
        int *inputData = new int[command[1]];
        MPI_Bcast(inputData, command[1], MPI_INT, id_root, MPI_COMM_WORLD);
        BinPacking binPacking = BinPacking::dataDeserialize(inputData, numThreads);
        delete[] inputData;
        run = true;

        while (run) {
            MPI_Recv(command, 2, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            switch (command[0]) {
                case -1: {
                    stop = true;
                    break;
                }
                case 0: {
                    run = false;
                    break;
                }
                case 2: {
                    int *inputData = (int *) malloc(command[1] * sizeof(int));
                    MPI_Recv(inputData, command[1], MPI_INT, id_root, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    Branch branch = binPacking.branchDeserialize(inputData);
                    free(inputData);

                    binPacking.BNB(branch);
                    break;
                }
            }
        }

    }
}

int main(int argc, char *argv[]) {
    const int num_threads = 8; //Set number of threads
    string path = "./bin1data/"; //Path of data

    int myid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (myid == 0) {
        ReadFiles readFiles(path);
        readFiles.sortDirs();
        for (int i = 0; i < readFiles.getNumOfFiles(); ++i) {
            cout << i << ". " << readFiles.getFileName(i) << endl;

            BinPacking binPacking = readFiles.getData(i, num_threads);
            std::vector<int> inputData = binPacking.getSerializeInputData();

            Branch branch = binPacking.init();
            if (binPacking.resFound()) {
                //Got result
            } else {
                int command[2]{1, (int) inputData.size()};
                MPI_Bcast(command, 2, MPI_INT, id_root, MPI_COMM_WORLD);
                MPI_Bcast(&inputData.front(), command[1], MPI_INT, 0, MPI_COMM_WORLD);

                //send branch to one of node
                std::vector<int> serialBranch = binPacking.branchSerialization(branch);
                command[0] = 2;
                command[1] = (int) serialBranch.size();
                MPI_Send(command, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
                MPI_Send(&serialBranch.front(), command[1], MPI_INT, 1, 1, MPI_COMM_WORLD);
            }

        }
    } else {

    }
    return 0;
}
