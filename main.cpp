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

DataInput getData(const string &filename) {
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

    return DataInput(n, c, items);
}



int main() {
    omp_set_num_threads(8);
//    printf("%d\n", omp_get_max_threads() - omp_get_num_threads());
    string path = "./bin1data/";
    vector<string> files = readFileDir(path);
    for (int i = 0; i < files.size(); ++i) {
//        if (i==10||i==11) continue;
        printf("%d. filename: %s\n", i, files[i].c_str());
        string fileName = path;
        fileName.append(files[i]);
        DataInput data = getData(fileName);
        clock_t start, end;
        start = clock();

        int result = BNB(data);
        end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        printf("Number of bins needed = %d\nTime=%lf\n", result, time);
    }

    return 0;
}
