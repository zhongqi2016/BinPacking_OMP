#include "Algorithm.h"


using namespace std;



vector<string> readFileDir(const string &PATH) {
    struct dirent *ptr;
    DIR *dir;
    dir = opendir(PATH.c_str());
    vector<string> files;
    while ((ptr = readdir(dir)) != nullptr) {
        if (ptr->d_name[0] == '.')
            continue;
//        printf("%s\n", ptr->d_name);
        files.emplace_back(ptr->d_name);
    }
    return files;
}

BinPacking getData(const string &filename) {
    int n, c;
    vector<int> items;

    ifstream infile(filename);
    string line;

    getline(infile, line);
    istringstream iss_n(line);
    iss_n >> n;
    getline(infile, line);
    istringstream iss_c(line);
    iss_c >> c;

    items.reserve(n);

    while (getline(infile, line)) {
        int num;
        istringstream iss(line);
        iss >> num;
        items.emplace_back(num);
    }
    infile.close();

    return BinPacking(c, items);
}



int main() {
    int num_threads=8;
    string path = "./bin1data/";
    omp_set_num_threads(num_threads);
//    printf("%d\n", omp_get_max_threads() - omp_get_num_threads());

    vector<string> files = readFileDir(path);
    for (int i = 0; i < files.size(); ++i) {
//        if (i==10||i==11) continue;
        printf("%d. filename: %s\n", i, files[i].c_str());
        string fileName = path;
        fileName.append(files[i]);
        BinPacking binPacking = std::move(getData(fileName));
        double start, end;
        start = omp_get_wtime();
        int result = binPacking.BNB();
        end = omp_get_wtime();
        double time = (double) (end - start);
        printf("Number of bins needed = %d\nTime=%lf\n", result, time);
    }

    return 0;
}
